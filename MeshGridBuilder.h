/*=============================================================================
 *
 *  Copyright (c) 2019 Sunnybrook Research Institute
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *=============================================================================*/

#ifndef SEDEEN_SRC_SPARSEHEATMAPBUILDER_SPARSEHEATMAPBUILDER_H
#define SEDEEN_SRC_SPARSEHEATMAPBUILDER_SPARSEHEATMAPBUILDER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
	bool creatMeshGrid(const std::string&, sedeen::Rect, std::vector<MeshGridBuilder::DataPoint>& , cv::Mat& );
	sedeen::Rect getROI(void);
	double inline getTileSize(void){ return tileSize_;};

protected:
	std::string m_path_to_image;
	double xscale_;
	double yscale_;
	sedeen::Size downsample_size_;
	double tileSize_;

};

#endif

