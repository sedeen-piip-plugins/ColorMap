/*=========================================================================
 *
 *  Copyright (c) 2019 Sunnybrook Research Institute
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef SEDEEN_SRC_PLUGINS_COLORMAP_COLORMAP_H
#define SEDEEN_SRC_PLUGINS_COLORMAP_COLORMAP_H

 // System headers
#include <memory>
#include <time.h>
#include <fstream>
#include <windows.h>

//Sedeen required headers
#include "algorithm/AlgorithmBase.h"
#include "algorithm/Parameters.h"
#include "algorithm/Results.h"
#include "archive/Session.h"
//

//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "MeshGridBuilder.h"

namespace sedeen {   
namespace algorithm {

/// A uniform sampling utility based on principles of stereology 
//
/// Generates uniformly spaced and sized circular contours useful for sampling
/// a large image.
class ColorMap : public AlgorithmBase {
public:
	// Constructor
	ColorMap();
	// Destructor
	virtual ~ColorMap();

private:
	virtual void run();

	virtual void init(const image::ImageHandle& image);

	/// Check if the parameters have changed since the last invocation.
	//
	/// \return
	/// \c true if any of the parameters differ from their previously-cached
	/// counterparts, \c false otherwise.
	bool parametersChanged();

	void creatHeatMap(image::RawImage& outputImage);

	double round(double val);

	cv::Vec3b interpolate(const cv::Vec3b color1, const cv::Vec3b color2, const float value);

	/// Dimensions of the down-sampled image to use for processing
	Size downsample_size_;

	///Scale factor to down-sampled image for processing
	double xscale_;
	double yscale_;

	std::vector<MeshGridBuilder::DataPoint> points_;
	//cv::Mat meshGrid_;

	//DoubleParameter transparency_;
	IntegerParameter transparency_;

	/// The display area parameter
	algorithm::DisplayAreaParameter display_area_;

	OpenFileDialogParameter openFileDialogParam_;
	std::string selectedFileTobeProcessed_;

	/// Image result reporter through which results are displayed
	ImageResult display_result_;

	// std::ofstream log_file;
};

} // namespace algorithm
} // namespace sedeen

#endif