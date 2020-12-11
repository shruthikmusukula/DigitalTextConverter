#include "core/image_processor.h"

using cv::bilateralFilter;
using cv::cvtColor;
using cv::destroyWindow;
using cv::imread;
using cv::Mat;
using cv::medianBlur;
using cv::Size;
using cv::threshold;
using cv::waitKey;

namespace digitaltextconverter {

namespace core {

void ImageProcessor::TransformImage(const std::string &filepath) const {
  // Read in image
  Mat img = imread(filepath, cv::IMREAD_COLOR);
  Mat transformed_img; // Additional matrix for loading transformed image

  // Apply filters and thresholding
  cv::bilateralFilter(img, transformed_img, kPixelDiameter, kSigmaValue,
                      kSigmaValue);
  cvtColor(transformed_img, transformed_img, cv::COLOR_BGR2RGB);
  cv::resize(transformed_img, transformed_img,
             Size(kResizeDimensions, kResizeDimensions));
  cv::threshold(transformed_img, transformed_img, kThreshold, kMaxPixelValue,
                cv::THRESH_BINARY_INV);
  cvtColor(transformed_img, transformed_img, cv::COLOR_RGB2GRAY);

  // Write processed image output
  imwrite(kProcessedImageFilepath, transformed_img);
}

} // namespace core

} // namespace digitaltextconverter