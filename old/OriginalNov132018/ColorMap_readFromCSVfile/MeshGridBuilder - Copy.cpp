#include "MeshGridBuilder.h"

MeshGridBuilder::MeshGridBuilder(const std::string& path_to_image , double xscale, double yscale, sedeen::Size image_size):
	m_path_to_image(path_to_image),
	xscale_(xscale),
	yscale_(yscale),
	downsample_size_(image_size)
{
	 /* log_file = std::ofstream(
        "log_file.txt", std::ios_base::out | std::ios_base::app );*/


}

MeshGridBuilder::~MeshGridBuilder(void)
{
}

bool MeshGridBuilder::creatMeshGrid(const std::string& selectedFileTobeProcessed, std::vector<MeshGridBuilder::DataPoint>& points, cv::Mat& meshGrid )
{
	std::ifstream file(selectedFileTobeProcessed);

	if (!file.is_open())
	{
		return false;
	}
	std::string line;

	cv::Mat child_meshGrid(downsample_size_.height(), downsample_size_.width(), CV_32FC1, cv::Scalar(0.0));
	while( std::getline(file, line) )
	{
		float color_code =0.1f;
		std::stringstream lineStream(line);
		MeshGridBuilder::DataPoint dp;
		lineStream >> dp.tlpy;
		lineStream >> dp.brpy;
		lineStream >> dp.tlpx;
		lineStream >> dp.brpx;
		lineStream >> dp.cellularity;
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
		child_meshGrid = cv::Scalar(0.0);
		cv::Point top_left(dp.tlpx*xscale_, dp.tlpy*yscale_);
		cv::Point bottom_right(dp.brpx*xscale_, dp.brpy*yscale_);
		cv::rectangle(child_meshGrid, top_left,  bottom_right, color_code, -1, 8); // (1.0 - 0.3*(3-dp.cellularity))
		cv::bitwise_or(child_meshGrid, meshGrid, meshGrid);
	}
	file.close();

	return !file.bad() && file.eof();
}

sedeen::Rect MeshGridBuilder::getROI(void){ return sedeen::Rect(sedeen::Point(0,0), sedeen::Size(10, 10)); };
