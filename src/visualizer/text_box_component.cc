#include "visualizer/text_box_component.h"

namespace digitaltextconverter {

namespace visualizer {

void TextBoxComponent::Setup() {
  text_ = "";
  Render();
}

void TextBoxComponent::KeyDown(const KeyEvent &event) {
  // Ignore other keyboard controls and check that user entry is a valid
  // keyboard character
  if ((event.getCode() != KeyEvent::KEY_ESCAPE) &&
      (event.getCode() != KeyEvent::KEY_DELETE) &&
      (event.getCode() != KeyEvent::KEY_RETURN) && (event.getCharUtf32())) {
    std::u32string strUtf32(1, event.getCharUtf32());
    std::string str = ci::toUtf8(strUtf32);

    text_ += str;
    Render();
  }
}

void TextBoxComponent::DeleteChar() {
  // Only delete character if user has already entered text
  if (text_.size() > 0) {
    text_ = text_.erase(text_.size() - 1);
    Render();
  }
}

void TextBoxComponent::Draw(const double window_size, const double margin) const {
  // Blend text box component with app background
  ci::gl::setMatricesWindow(ci::app::getWindowSize());
  ci::gl::enableAlphaBlending();
  ci::gl::ScopedBlend alphaBlend(true);
  ci::gl::ScopedColor color(ci::ColorA(1, 1, 1, 1));

  // Draw text box only if texture object exists
  if (text_texture_)
    ci::gl::draw(text_texture_, vec2(window_size - 50, window_size - margin));

  // Draw textbox border
  vec2 pixel_top_left =
      vec2(window_size - 50 - kLineWidth, window_size - margin - kLineWidth);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(size_.x + kLineWidth, size_.y + kLineWidth);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(pixel_bounding_box, kLineWidth);
}

string& TextBoxComponent::GetText() {
  return text_;
}

void TextBoxComponent::SetText(const string &text) {
  text_ = text;
}

void TextBoxComponent::Render() {
  ci::TextBox tbox = ci::TextBox()
                         .alignment(ci::TextBox::CENTER)
                         .font(font_)
                         .size(glm::ivec2(size_.x, size_.y))
                         .text(text_);
  tbox.setColor(ci::ColorA(255.0f, 255.0f, 255.0f, 1.0f));
  tbox.setBackgroundColor(ci::ColorA(0.0f, 0.0f, 0.0f, 0.0f));
  text_texture_ = ci::gl::Texture2d::create(tbox.render());
}

} // namespace visualizer

} // namespace digitaltextconverter