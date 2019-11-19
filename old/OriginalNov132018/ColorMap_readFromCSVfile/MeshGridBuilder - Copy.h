#ifndef SEDEEN_SRC_SPARSEHEATMAPBUILDER_SPARSEHEATMAPBUILDER_H
#define SEDEEN_SRC_SPARSEHEATMAPBUILDER_SPARSEHEATMAPBUILDER_H

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Global.h"
#include <fstream>

class MeshGridBuilder
{
public:
	MeshGridBuilder(const std::string& , double, double, sedeen::Size image_size);
	~MeshGridBuilder(void);

	struct DataPoint
	{
		double tlpx;
		double tlpy;
		double brpx;
		double brpy;
		float cellularity;
	};
	bool creatMeshGrid(const std::string&, std::vector<MeshGridBuilder::DataPoint>& , cv::Mat& );
	sedeen::Rect getROI(void);

protected:
	std::string m_path_to_image;
	double xscale_;
	double yscale_;
	sedeen::Size downsample_size_;

private:

	 /*std::ofstream log_file;*/
	
};


#endif

