#include "core/text_converter.h"

#ifdef __cplusplus
#undef NO
#undef YES
#include <opencv2/opencv.hpp>
#endif

#include <opencv2/text/ocr.hpp>

#include <fstream>

using cv::imread;
using cv::IMREAD_COLOR;
using cv::Mat;

using std::ofstream;

namespace digitaltextconverter {

namespace core {

string TextConverter::GetOutput(const string &filepath) const {
  // Provide detected output using OCRTesseract
  Mat img = imread(filepath, IMREAD_COLOR);
  static auto tess = cv::text::OCRTesseract::create(
      NULL /*datapath*/, "eng" /*lang*/, NULL, kOCREngineMode /*oem*/,
      kPageSegmentationMode /*psmode*/);
  string output;
  tess->run(img, output, NULL, NULL, NULL, kComponentLevel);
  return output;
}

void TextConverter::WriteOutput(const string &text,
                                const string &filepath) const {
  ofstream output_file(filepath);
  output_file << text;
}

} // namespace core

} // namespace digitaltextconverter