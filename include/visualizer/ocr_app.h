#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <core/image_processor.h>
#include <core/text_converter.h>
#include <visualizer/sketchpad.h>
#include <visualizer/text_box_component.h>

using ci::app::KeyEvent;
using ci::app::MouseEvent;

using ci::Font;

using digitaltextconverter::core::ImageProcessor;
using digitaltextconverter::core::TextConverter;

using std::string;
using std::unordered_map;

namespace digitaltextconverter {

namespace visualizer {

/**
 * Allows a user to draw text on a sketchpad and classify it.
 */
class OCRApp : public ci::app::App {
public:
  /** Loads model and classifier for use in application. */
  OCRApp();
  /** Draws major app elements like sketchpad, instructions and color guide. */
  void draw() override;
  /** Adds user locations that the user draws on to the sketchpad strokes.
   * @param event - the current user's cursor event
   */
  void mouseDrag(MouseEvent event) override;
  /**
   * Adds current user stroke to the sketchpad.
   * @param event the current user's cursor event
   */
  void mouseUp(MouseEvent event) override;
  /**
   * Changes drawing color, clears sketchpad, or undoes latest user action based
   * on keyboard input.
   * @param event - the current user's keyboard input
   */
  void keyDown(KeyEvent event) override;

private:
  /** The current window size */
  static constexpr double kWindowSize = 800.0;
  /** The current margin size for the sketchpad */
  static constexpr double kMargin = kWindowSize / 8.0;
  /** Standard font configuration */
  const Font kLabelFont = Font("Helvetica", 20);
  /** Standard container line width */
  static constexpr double kLineWidth = 3.5;
  /** Represents each color as a key in the kColors map */
  enum ColorKeys { WHITE = 1, RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, PINK };
  /** Map of possible sketchpad colors */
  const unordered_map<size_t, string> kColors = {
      {1, "white"},  {2, "red"},    {3, "blue"},   {4, "green"},
      {5, "yellow"}, {6, "purple"}, {7, "orange"}, {8, "pink"}};
  /** Tracker for current color key */
  size_t current_color_index_;
  /** Sketchpad object for recording user input */
  Sketchpad sketchpad_;
  /** TextBox Component for user input */
  TextBoxComponent box_;
  /** Image Processor object for applying image transformations */
  ImageProcessor processor_;
  /** Text Converter object for obtaining converted text */
  TextConverter text_processor_;
  /** Live output tracker for recognized text */
  string output_;
  /** Adds label for current color. */
  void DrawCurrentColor();
  /** Adds labels for all color options. */
  void DrawColors();
  /** Adds textbox details. */
  void DrawTextBox();
  /** Takes and saves sketchpad screenshot. */
  void TakeSketchpadScreenshot();
};

} // namespace visualizer

} // namespace digitaltextconverter
