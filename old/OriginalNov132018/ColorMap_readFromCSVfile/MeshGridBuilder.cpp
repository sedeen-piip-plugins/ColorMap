#include "MeshGridBuilder.h"

MeshGridBuilder::MeshGridBuilder(const std::string& path_to_image , double xscale, double yscale, sedeen::Size image_size):
	m_path_to_image(path_to_image),
	xscale_(xscale),
	yscale_(yscale),
	downsample_size_(image_size),
	tileSize_(1)
{
	  /*log_file = std::ofstream(
        "log_file_1.txt", std::ios_base::out | std::ios_base::app );*/


}

MeshGridBuilder::~MeshGridBuilder(void)
{
}

bool MeshGridBuilder::creatMeshGrid(const std::string& selectedFileTobeProcessed, 
					sedeen::Rect display_region, std::vector<MeshGridBuilder::DataPoint>& points,
					cv::Mat& meshGrid )
{
	double xshift = display_region.x();
	double yshift = display_region.y();

	double tileSize =1;

	std::ifstream file(selectedFileTobeProcessed);

	if (!file.is_open())
	{
		return false;
	}
	std::string line;

	cv::Mat child_meshGrid(downsample_size_.height(), downsample_size_.width(), CV_32FC1, cv::Scalar(0.0));
	while( std::getline(file, line) )
	{
		std::stringstream lineStream(line);
		MeshGridBuilder::DataPoint dp;
		lineStream >> dp.tlpy;
		lineStream >> dp.brpy;
		lineStream >> dp.tlpx;
		lineStream >> dp.brpx;
		lineStream >> dp.cellularity;

		tileSize_ = (int)dp.brpy -(int)dp.tlpy; 

		float color_code =0.1f;
		switch(int(dp.cellularity))
		{
		case 0:
			color_code = 0.5;
			break;
		case 1:
			color_code = 0.6f;
			break;
		case 2:
			color_code = 0.8f;
			break;
		case 3:
			color_code = 1.0f;
			break;
		}
		points.push_back(dp);

		auto ptl = sedeen::Point((int)dp.tlpx, (int)dp.tlpy);
		auto pbr = sedeen::Point((int)dp.brpx, (int)dp.brpy);

		if( display_region.contains(ptl) || display_region.contains(pbr) )
		{
			child_meshGrid = cv::Scalar(0.0);
			cv::Point2d top_left((dp.tlpx-xshift)*xscale_, (dp.tlpy-yshift)*yscale_);
			cv::Point2d bottom_right((dp.brpx-xshift)*xscale_, (dp.brpy-yshift)*yscale_); 
			cv::rectangle(child_meshGrid, top_left,  bottom_right, color_code, -1, 8); // (1.0 - 0.3*(3-dp.cellularity))
			cv::bitwise_or(child_meshGrid, meshGrid, meshGrid);
		}
		
	}
	file.close();

	return !file.bad() && file.eof();
}

sedeen::Rect MeshGridBuilder::getROI(void){ return sedeen::Rect(sedeen::Point(0,0), sedeen::Size(10, 10)); };