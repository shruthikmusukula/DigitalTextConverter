#pragma once

#include "cinder/Log.h"
#include "cinder/Text.h"
#include "cinder/Unicode.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"

using ci::Font;
using ci::app::KeyEvent;
using ci::gl::TextureRef;

using glm::vec2;

using std::string;

namespace digitaltextconverter {

namespace visualizer {

/**
 * Represents a text-box component for obtaining user input in the OCR app.
 * Inspiration from:
 * https://github.com/cinder/Cinder/blob/master/samples/TextBox/src/TextBoxApp.cpp
 */
class TextBoxComponent {
public:
  /** Initializes basic member variables for the TextBoxComponent. */
  void Setup();
  /**
   * Adds text to text box component based on user input.
   * @param event - the current key event object
   */
  void KeyDown(const KeyEvent &event);
  /** Deletes the last character of user text input. */
  void DeleteChar();
  /**
   * Draws the current text box component.
   * @param window_size - the app window size
   * @param margin - the margin size for the app
   */
  void Draw(const double window_size, const double margin) const;
  /**
   * Returns the entered text in the textbox.
   * @return the string content of the textbox content
   */
  string& GetText();
  /**
   * Updates text in the component.
   * @param text - the text to set the text content to
   */
  void SetText(const string &text);

private:
  /** The line width for the text box border */
  static constexpr double kLineWidth = 3.5;
  /** The current text inside the text box */
  string text_;
  /** The current text box texture object */
  TextureRef text_texture_;
  /** The text box size */
  const vec2 size_ = vec2(200, 50);
  /** The font size for text entered in the text box */
  const size_t kFontSize = 16;
  /** The font for the text inside the text box */
  const Font font_ = Font("Helvetica", kFontSize);
  /** Updates the text box texture object with recent updates */
  void Render();
};

} // namespace visualizer

} // namespace digitaltextconverter
