#ifdef __cplusplus
#undef NO
#undef YES
#include <opencv2/opencv.hpp>
#endif
#include <opencv2/text/ocr.hpp>

#include "cli/command_line_input_parser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

using digitaltextconverter::cli::CommandLineInputParser;
using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::ifstream;
using std::ofstream;
using std::string;

int main(const int argc, const char **argv) {
  // Handled CLI Cases:
  // .input_image --load --image_path /Users/shruthikmusukula/Desktop/test.jpeg --save --output_file /Users/shruthikmusukula/Desktop/output.txt
  // .input_image --load --image_path /Users/shruthikmusukula/Desktop/test.jpeg
  // .input_image --help

  // Set up and initialize cli_parser for current program execution
  CommandLineInputParser cli_parser = CommandLineInputParser(argc, argv);

  try {
    cli_parser.options = cli_parser.ProcessUserOptions();
  } catch (exception &ex) {
    cerr << "Review the valid options below and try again. Remember to provide "
            "valid filepaths. Error: "
         << ex.what() << endl;
  }

  // Exit concept from:
  // https://sodocumentation.net/boost/topic/5359/boost-program-options
  if (cli_parser.options.exit) {
    return 0;
  }

  // Load up image, Tesseract engine, and output string
  cv::Mat img;
  static auto tess = cv::text::OCRTesseract::create(
      NULL /*datapath*/, "eng" /*lang*/, NULL, 3 /*oem*/, 3 /*psmode*/);
  std::string output;

  // Handle actions for load command
  if (cli_parser.options.load) {
    img = imread(cli_parser.options.image_path, cv::IMREAD_COLOR);
  }

  // Produce output
  tess->run(img, output, NULL, NULL, NULL, 0);

  // Handle actions for save command
  if (cli_parser.options.save) {
    // Write output to provided filepath
    ofstream training_output(cli_parser.options.output_file);
    training_output << output;
  } else {
    // Print output in console
    std::cout << output << std::endl;
  }

  return 0;
}
