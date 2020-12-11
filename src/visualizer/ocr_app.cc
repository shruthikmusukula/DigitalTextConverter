#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

#include <visualizer/ocr_app.h>

using ci::gl::clear;
using ci::gl::drawSolidRect;
using ci::gl::drawStringCentered;

using ci::Rectf;

using glm::vec2;

using std::to_string;

namespace digitaltextconverter {

namespace visualizer {

OCRApp::OCRApp()
    : current_color_index_(1),
      sketchpad_(vec2(kMargin, kMargin), kWindowSize - 2 * kMargin) {
  // Set App Window size
  ci::app::setWindowSize((int)5 * kWindowSize / 4, (int)kWindowSize);
  box_.Setup();
}

void OCRApp::draw() {
  clear(ci::Color::gray(0.1f)); // gray background color

  sketchpad_.Draw(kColors.at(current_color_index_).c_str());
  drawStringCentered(
      "Press Esc to clear the sketchpad, Delete to undo your last",
      vec2(kWindowSize / 2 - (kMargin / 4), kMargin / 2 - (kMargin / 4)),
      ci::Color("white"), kLabelFont);

  drawStringCentered(
      "action, or Enter to build your output. Begin typing to enter",
      vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"), kLabelFont);

  drawStringCentered(
      "your output filepath in the textbox below.",
      vec2(kWindowSize / 2 + (kMargin / 4), kMargin / 2 + (kMargin / 4)),
      ci::Color("white"), kLabelFont);

  drawStringCentered("Live Output: " + output_,
                     vec2(kWindowSize / 2, kWindowSize - kMargin / 2),
                     ci::Color("white"), kLabelFont);

  DrawCurrentColor();
  DrawColors();
  DrawTextBox();
}

void OCRApp::DrawCurrentColor() {
  // Draw Current Color Label
  vec2 label_location(33 * kWindowSize / 32, kMargin);
  drawStringCentered("Current Color: ", label_location, ci::Color("white"),
                     kLabelFont);

  // Draw Current Color Preview
  vec2 pixel_top_left(label_location.x + (3 * kMargin / 4),
                      label_location.y - (kMargin / 10));
  vec2 pixel_bottom_right = pixel_top_left + vec2(kMargin / 4, kMargin / 4);
  Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
  ci::gl::color(ci::Color(kColors.at(current_color_index_).c_str()));
  drawSolidRect(pixel_bounding_box);
}

void OCRApp::DrawColors() {
  vec2 label_location(17 * kWindowSize / 16, kMargin * 2);
  drawStringCentered("Color Guide", label_location, ci::Color("white"),
                     kLabelFont);

  size_t x_cor = 33 * kWindowSize / 32;
  size_t y_cor = label_location.y + (kMargin / 2);
  for (size_t key = 1; key <= kColors.size(); ++key) {
    // Individual Color Label
    drawStringCentered(to_string(key) + " - " + kColors.at(key),
                       vec2(x_cor, y_cor), ci::Color("white"), kLabelFont);

    // Color Preview
    vec2 pixel_top_left(x_cor + (3 * kMargin / 4), y_cor - (kMargin / 10));
    vec2 pixel_bottom_right = pixel_top_left + vec2(kMargin / 4, kMargin / 4);
    Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
    ci::gl::color(ci::Color(kColors.at(key).c_str()));
    drawSolidRect(pixel_bounding_box);

    // Update y_cor accordingly
    y_cor += (kMargin / 2);
  }
}

void OCRApp::DrawTextBox() {
  vec2 label_location(kWindowSize + 50, kWindowSize - 125);
  drawStringCentered("Output Filepath:", label_location, ci::Color("white"),
                     kLabelFont);
  box_.Draw(kWindowSize, kMargin);
}

void OCRApp::mouseDrag(MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void OCRApp::mouseUp(MouseEvent event) {
  sketchpad_.UpdateStrokes(kColors.at(current_color_index_));
}

void OCRApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
  case KeyEvent::KEY_1:
    // Set color to white
    current_color_index_ = ColorKeys::WHITE;
    break;
  case KeyEvent::KEY_2:
    // Set color to red
    current_color_index_ = ColorKeys::RED;
    break;
  case KeyEvent::KEY_3:
    // Set color to blue
    current_color_index_ = ColorKeys::BLUE;
    break;
  case KeyEvent::KEY_4:
    // Set color to green
    current_color_index_ = ColorKeys::GREEN;
    break;
  case KeyEvent::KEY_5:
    // Set color to yellow
    current_color_index_ = ColorKeys::YELLOW;
    break;
  case KeyEvent::KEY_6:
    // Set color to purple
    current_color_index_ = ColorKeys::PURPLE;
    break;
  case KeyEvent::KEY_7:
    // Set color to orange
    current_color_index_ = ColorKeys::ORANGE;
    break;
  case KeyEvent::KEY_8:
    // Set color to pink
    current_color_index_ = ColorKeys::PINK;
    break;
  case KeyEvent::KEY_DELETE:
    // Clear latest drawing element
    sketchpad_.UndoStroke();
    break;
  case KeyEvent::KEY_RETURN:
    // Take screenshot, process image, update current prediction, and write to
    // file if path was provided
    TakeSketchpadScreenshot();
    processor_.TransformImage("data/output.png");
    output_ = text_processor_.GetOutput("data/transformed_output.png");
    if (output_.size() > 0 && box_.GetText().size() > 0) {
      text_processor_.WriteOutput(output_, box_.GetText());
    }
    break;
  case KeyEvent::KEY_ESCAPE:
    // Empties all sketchpad content
    sketchpad_.Clear();
    output_ = "";
    break;
  case KeyEvent::KEY_BACKSPACE:
    // Clear latest drawing element
    box_.DeleteChar();
    break;
  default:
    box_.KeyDown(event);
    break;
  }
}

void OCRApp::TakeSketchpadScreenshot() {
  writeImage(
      ci::fs::path("data/output.png"),
      copyWindowSurface(ci::Area(kMargin + kLineWidth, kMargin + kLineWidth,
                                 kWindowSize - kMargin - kLineWidth,
                                 kWindowSize - kMargin - kLineWidth)));
}

} // namespace visualizer

} // namespace digitaltextconverter