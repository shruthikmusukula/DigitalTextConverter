#include <visualizer/ocr_app.h>

using digitaltextconverter::visualizer::OCRApp;

void prepareSettings(OCRApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(OCRApp, ci::app::RendererGl, prepareSettings);