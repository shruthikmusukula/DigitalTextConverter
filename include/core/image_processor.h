#pragma once

#ifdef __cplusplus
#undef NO
#undef YES
#include <opencv2/opencv.hpp>
#endif

#include <string>

using cv::Mat;

using std::string;

namespace digitaltextconverter {

namespace core {

/**
 * An image pre-processing class using OpenCV
 */
class ImageProcessor {
public:
  /**
   * Applies image transformations to given sketchpad screenshot.
   * @param filepath - the filepath of the sketchpad screenshot
   */
  void TransformImage(const string &filepath) const;

private:
  /** Pixel diameter for bilateral filtering */
  const size_t kPixelDiameter = 9;
  /** Sigma constant for bilateral filtering */
  const size_t kSigmaValue = 75;
  /** Image dimensions for resizing and increasing image resolution */
  const size_t kResizeDimensions = 1000;
  /** Pixel threshold value for apply binary inversion thresholding */
  const size_t kThreshold = 25;
  /** Max pixel value */
  const size_t kMaxPixelValue = 255;
  /** Transformed image output filepath */
  const string kProcessedImageFilepath = "data/transformed_output.png";
};

} // namespace core

} // namespace digitaltextconverter
