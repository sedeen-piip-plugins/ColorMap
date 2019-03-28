#ifndef DPTK_SRC_PLUGINS_HEATMAPBUILDER_HEATMAPBUILDER_H
#define DPTK_SRC_PLUGINS_HEATMAPBUILDER_HEATMAPBUILDER_H

// System headers
#include <memory>
#include <time.h>
#include <fstream>
#include <windows.h>

// DPTK headers - a minimal set
#include "algorithm/AlgorithmBase.h"
#include "algorithm/Parameters.h"
#include "algorithm/Results.h"
#include "archive/Session.h"

//#include <opencv2/contrib/contrib.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\imgcodecs.hpp"

#include "MeshGridBuilder.h"

namespace sedeen {
namespace algorithm {	

/// A uniform sampling utility based on principles of stereology 
//
/// Generates uniformly spaced and sized circular contours useful for sampling
/// a large image.
class ColorMapBuilder : public AlgorithmBase {
 public:
  ColorMapBuilder();

  virtual ~ColorMapBuilder();

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
