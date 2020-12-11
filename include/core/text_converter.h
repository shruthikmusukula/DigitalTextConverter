#pragma once

#include <string>

using std::string;

namespace digitaltextconverter {

namespace core {

/**
 * Extracts text from a pre-processed image containing written text
 */
class TextConverter {
public:
  /**
   * Returns the converted string output of the user's written text.
   * @param filepath - the filepath of the processed image
   * @return string output of user's written text
   */
  string GetOutput(const string &filepath) const;
  /**
   * Writes the user's written text as digital text to a filepath of their
   * choice.
   * @param text - the outputted text to write
   * @param filepath - the filepath to write text to
   */
  void WriteOutput(const string &text, const string &filepath) const;

private:
  /** OCR Engine Mode */
  const size_t kOCREngineMode = 3;
  /** Tesseract Page Segmentation Mode */
  const size_t kPageSegmentationMode = 7;
  /** Tesseract Image Component Level */
  const size_t kComponentLevel = 0;
};

} // namespace core

} // namespace digitaltextconverter
