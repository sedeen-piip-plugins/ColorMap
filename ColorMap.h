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

#ifndef SEDEEN_SRC_PLUGINS_COLORMAP_COLORMAP_H
#define SEDEEN_SRC_PLUGINS_COLORMAP_COLORMAP_H

 // System headers
#include <memory>
#include <ctime>
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

	IntegerParameter transparency_;

	/// The display area parameter
	algorithm::DisplayAreaParameter display_area_;

	OpenFileDialogParameter openFileDialogParam_;
	std::string selectedFileTobeProcessed_;

	/// Image result reporter through which results are displayed
	ImageResult display_result_;
};

} // namespace algorithm
} // namespace sedeen

#endif