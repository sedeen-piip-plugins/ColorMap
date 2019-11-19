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
		//log_file = std::ofstream("log_file_1.txt", std::ios_base::out | std::ios_base::app );
		
}

ColorMapBuilder::~ColorMapBuilder() {
}

void ColorMapBuilder::run() {

	auto display_area_isChanged = display_area_.isChanged();
	DisplayRegion display_region = display_area_;
	downsample_size_= display_region.output_size;
	xscale_ = (double)(display_region.output_size.width())/(double)display_region.source_region.width();
	yscale_ = (double)(display_region.output_size.height())/(double)display_region.source_region.height();

	image::RawImage outputImage(downsample_size_, ColorSpace(ColorModel::RGBA, ChannelType::UInt8));
	outputImage.fill(0);	
	if(parametersChanged() || display_area_isChanged) {
		creatHeatMap(outputImage);
		display_result_.update(outputImage, display_region.source_region);
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

	DisplayRegion display_region = display_area_;
	auto region = display_region.source_region;

	image::tile::Compositor compositor(source_factory);
	outputImage = compositor.getImage(display_region.source_region, display_region.output_size);

	points_.clear();

	meshGrid_ = cv::Mat(downsample_size_.height(), downsample_size_.width(), CV_32FC1, cv::Scalar(0));
	MeshGridBuilder * mBuilder = new MeshGridBuilder(path_to_image, xscale_, yscale_, downsample_size_);
	bool isMeshCreated = mBuilder->creatMeshGrid(selectedFileTobeProcessed_, region, points_, meshGrid_);
	if(!isMeshCreated)
	{
		delete mBuilder;
		throw std::runtime_error("Not able to built the Mesh Grid to compute the Heat Map!");
	}
	double tileSize = mBuilder->getTileSize();
	delete mBuilder;

	float g_max_transparency = double(transparency_)/100.0f;
	cv::Mat heatmap = cv::Mat::zeros(downsample_size_.height(), downsample_size_.width(), CV_32FC1);
	heatmap = meshGrid_.clone();
	meshGrid_= cv::Mat();

	double dummyValue = 1.5;
	cv::Mat temp_map;
	int kernel_size = ((int)tileSize*xscale_> 3) ?(dummyValue*(int)tileSize*xscale_):3; //21
	kernel_size = kernel_size%2 == 0 ? (kernel_size-1): kernel_size;

	if(kernel_size >= tileSize )
	{
		kernel_size = (int)tileSize%2 == 0 ? (tileSize+1): tileSize;
	}

	if(!heatmap.empty()){
		cv::blur(heatmap, temp_map, cv::Size(kernel_size, kernel_size));
	}

	cv::Mat opencvMap, opencvColor;
	double min, max;
	cv::minMaxLoc(temp_map, &min, &max);
	cv::normalize(temp_map, opencvMap, 0, (int)255*max, cv::NORM_MINMAX, CV_8UC1);
	cv::applyColorMap(opencvMap, opencvColor, cv::COLORMAP_JET);

	double xshift = region.x()*xscale_;
	double yshift = region.y()*yscale_;
	image::Iterator it = getIterator(image(), region, downsample_size_);
	while(!it.finished())
	{
		auto position = Point(it.x(), it.y());
		int x = it.x() -  xshift;
		int y = it.y() -  yshift;
		if((!heatmap.empty())) { //region.contains(position) &&
			const float heat_mix = heatmap.at<float>(cv::Point(x, y));
			// in BGR
			const cv::Vec3b i_color((unsigned char)it.getComponent(2), 
				(unsigned char)it.getComponent(1), 
				(unsigned char)it.getComponent(0));

			const cv::Vec3b heat_color = opencvColor.at<cv::Vec3b>(cv::Point(x, y));
			const float heat_mix2 = std::min(heat_mix, g_max_transparency);
			const cv::Vec3b final_color = interpolate(i_color, heat_color, heat_mix2);
			for (int j=0; j<3; j++){
				outputImage.setValue(x, y, j, final_color[2-j]);
			}
		}

		//it++;
		it.advance();
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

	xscale_ = 1.0;
	yscale_ = 1.0;	
}

bool ColorMapBuilder::parametersChanged() {
  return transparency_.isChanged();
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
