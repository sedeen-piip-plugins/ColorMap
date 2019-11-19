#include "plugins\ColorMap\ColorMapBuilder.h"
#include <sstream>
#include <vector>

// DPTK headers
#include "Algorithm.h"
#include "Geometry.h"
#include "Global.h"
#include "Image.h"
#include "BindingsOpenCV.h"


// Poco header needed for the macros below 
#include <Poco/ClassLibrary.h>

// Declare that this object has AlgorithmBase subclasses
//  and declare each of those sub-classes
POCO_BEGIN_MANIFEST(sedeen::algorithm::AlgorithmBase)
POCO_EXPORT_CLASS(sedeen::algorithm::ColorMapBuilder)
POCO_END_MANIFEST

namespace sedeen {
namespace algorithm {

ColorMapBuilder::ColorMapBuilder()
	:xscale_(1.0),
	yscale_(1.0),
	transparency_(),
	display_area_(),
	openFileDialogParam_(),
	display_result_(){

}

ColorMapBuilder::~ColorMapBuilder() {
}

void ColorMapBuilder::run() {

	image::RawImage outputImage(downsample_size_, Color(ColorSpace::RGBA_8));
	outputImage.fill(0);
	if(parametersChanged()) {
		creatHeatMap(outputImage);

		auto source_region = image()->getFactory()->getLevelRegion(0);	
		display_result_.update(outputImage, source_region);
	}
}

void ColorMapBuilder::creatHeatMap(image::RawImage& outputImage)
{
	if ( selectedFileTobeProcessed_.empty() )
	{

		sedeen::algorithm::parameter::OpenFileDialog::DataType openFileDialogDataType = openFileDialogParam_;
		selectedFileTobeProcessed_ = openFileDialogDataType[0].getFilename();
		if (!openFileDialogParam_.isUserDefined() || selectedFileTobeProcessed_.empty())
		{
			/*msgBox.setText("Out put directory not set.");
			int ret = msgBox.exec();*/
			throw std::runtime_error("Please select a directory to save tiles!");
			//MessageBox(nullptr, LPCSTR("Please select a directory to save tiles!"), LPCSTR("Notification"), MB_OKCANCEL);
		}
	}

	std::string path_to_image = 
		  image()->getMetaData()->get(image::StringTags::SOURCE_DESCRIPTION, 0);
	 
	auto source_factory = image()->getFactory();
	auto smallest_level = source_factory->getNumLevels() - 1;
	auto smallest_region = source_factory->getLevelRegion(smallest_level);
	auto smallest_size = size(smallest_region);
	auto largest_region = source_factory->getLevelRegion(0);

	image::tile::Compositor compositor(source_factory);
	outputImage = compositor.getImage(largest_region, downsample_size_);

	float ratio_intensity = 150.0f;
	points_.clear();
	meshGrid_= cv::Mat();

	meshGrid_ = cv::Mat(downsample_size_.height(), downsample_size_.width(), CV_32FC1, cv::Scalar(0));
	MeshGridBuilder * mBuilder = new MeshGridBuilder(path_to_image, xscale_, yscale_, downsample_size_);
	mBuilder->creatMeshGrid(selectedFileTobeProcessed_, points_, meshGrid_);
	delete mBuilder;

	float g_max_transparency = double(transparency_)/100.0f;
	cv::Mat g_heatmap = cv::Mat::zeros(downsample_size_.height(), downsample_size_.width(), CV_32FC1);
	g_heatmap = meshGrid_.clone();

	cv::Mat temp_map;
	if(!g_heatmap.empty()){
		cv::blur(g_heatmap, temp_map, cv::Size(13, 13));
	}

	cv::Mat opencvMap, opencvColor;
	double min, max;
	cv::minMaxLoc(temp_map, &min, &max);
	cv::normalize(temp_map, opencvMap, 0, (int)255*max, cv::NORM_MINMAX, CV_8UC1);
	cv::applyColorMap(opencvMap, opencvColor, cv::COLORMAP_JET);
	cv::imwrite("opencvColor.png", opencvColor);

	image::Iterator it = getIterator(image(), largest_region, downsample_size_);
	while(!it.finished())
	{
		auto position = Point(it.x(), it.y());
		if(smallest_region.contains(position) && (!g_heatmap.empty())) {
			const float heat_mix = g_heatmap.at<float>(cv::Point(it.x(), it.y()));
			// in BGR
			const cv::Vec3b i_color((unsigned char)it.getComponent(2), 
				(unsigned char)it.getComponent(1), 
				(unsigned char)it.getComponent(0));

			const cv::Vec3b heat_color = opencvColor.at<cv::Vec3b>(cv::Point(it.x(), it.y()));
			const float heat_mix2 = std::min(heat_mix, g_max_transparency);
			const cv::Vec3b final_color = interpolate(i_color, heat_color, heat_mix2);

			for (int j=0; j<3; j++){
				outputImage.setValue(it.x(), it.y(), j, final_color[2-j]);
			}
		}

		it++;
	}

}

void ColorMapBuilder::init(const image::ImageHandle& input_image) {
	if (isNull(input_image)) return;
	// Create system parameter - provide information about current view in UI
    display_area_ = createDisplayAreaParameter(*this);
	// Bind display result image to UI
	display_result_ = createImageResult(*this, "Final Image");

	transparency_ = createIntegerParameter( // use the creation function
		*this, // reference to the algorithm
		"Transparency", // name
		"Set the max transparency of the overly heatmap", // description
		60, // default value
		0, // minimum allowed value
		100, // maximum allowed value
		false); // optional or not

	file::FileDialogOptions fileDialogOptions;
	file::FileDialogFilter fileDialogFilter;
	fileDialogFilter.name = "Comma-separated  text file (*.csv)";
	fileDialogOptions.filters.push_back(fileDialogFilter);
	openFileDialogParam_ = sedeen::algorithm::createOpenFileDialogParameter(*this,
		"Directory To open the probability file",
		"description",
		fileDialogOptions,
		false);

	//Determind the processed image size 
	auto source_factory = image()->getFactory();
	auto smallest_level = source_factory->getNumLevels() - 1;
	auto smallest_region = source_factory->getLevelRegion(smallest_level);
	auto smallest_size = size(smallest_region);

	auto largest_region = source_factory->getLevelRegion(0);
	auto largest_size = size(largest_region);

	double ratio = 0.6; // how to find the optimal scale factor
	xscale_ = (double)(ratio*smallest_size.width())/(double)largest_size.width();
	yscale_ = (double)(ratio*smallest_size.height())/(double)largest_size.height();

	downsample_size_ = sedeen::Size(ratio*smallest_size.width(), ratio*smallest_size.height());

}

bool ColorMapBuilder::parametersChanged() {
  return transparency_.isChanged() || display_area_.isChanged();
}

cv::Vec3b ColorMapBuilder::interpolate(const cv::Vec3b color1, const cv::Vec3b color2, const float value)
{
	uchar b = cv::saturate_cast<uchar>(round((1.0 - value)*color1.val[0] + value*color2.val[0]));
	uchar g = cv::saturate_cast<uchar>(round((1.0 - value)*color1.val[1] + value*color2.val[1]));
	uchar r = cv::saturate_cast<uchar>(round((1.0 - value)*color1.val[2] + value*color2.val[2]));

	return cv::Vec3b(b, g, r);
}

double ColorMapBuilder::round(double val)
{
	return floor(val + 0.5);
}

} // namespace algorithm
} // namespace sedeen
