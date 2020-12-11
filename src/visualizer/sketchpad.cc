#include <visualizer/sketchpad.h>

using ci::gl::begin;
using ci::gl::drawStrokedRect;
using ci::gl::end;
using ci::gl::vertex;

using ci::Rectf;

using glm::vec2;

using std::vector;

namespace digitaltextconverter {

namespace visualizer {

Sketchpad::Sketchpad(const vec2 &top_left_corner, double sketchpad_size)
    : side_length_(sketchpad_size), top_left_corner_(top_left_corner) {}

void Sketchpad::Draw(string color) {
  // Draw sketchpad rectangle
  vec2 pixel_top_left = top_left_corner_;
  vec2 pixel_bottom_right = pixel_top_left + vec2(side_length_, side_length_);
  Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  drawStrokedRect(pixel_bounding_box, kLineWidth);

  // Draw stored strokes_
  for (auto it : strokes_) {
    ci::gl::color(ci::Color(it.first.c_str()));
    for (vector<vec2> &stroke : it.second) {
      begin(GL_LINE_STRIP);
      for (vec2 &point : stroke) {
        vertex(point);
      }
      end();
    }
  }

  // Draw current stroke
  ci::gl::color(ci::Color(color.c_str()));
  begin(GL_LINE_STRIP);
  for (vec2 &point : points_) {
    vertex(point);
  }
  end();
}

void Sketchpad::HandleBrush(const vec2 &point_coords) {
  // Make sure sketchpad brush is in bounds
  if ((point_coords.x > top_left_corner_.x) &&
      (point_coords.x < top_left_corner_.x + side_length_) &&
      (point_coords.y > top_left_corner_.x) &&
      (point_coords.y < top_left_corner_.x + side_length_)) {
    points_.push_back(point_coords);

    // Increase brush thickness
    for (size_t index = 1; index <= kBrushSize; ++index) {
      points_.push_back(vec2(point_coords.x + index, point_coords.y + index));
      points_.push_back(vec2(point_coords.x - index, point_coords.y + index));
      points_.push_back(vec2(point_coords.x + index, point_coords.y - index));
      points_.push_back(vec2(point_coords.x - index, point_coords.y - index));
      points_.push_back(vec2(point_coords.x + index, point_coords.y));
      points_.push_back(vec2(point_coords.x - index, point_coords.y));
      points_.push_back(vec2(point_coords.x, point_coords.y + index));
      points_.push_back(vec2(point_coords.x, point_coords.y - index));
    }
  }
}

void Sketchpad::UpdateStrokes(const string current_color) {
  // Update stroke vector
  if (strokes_.find(current_color) == strokes_.end()) {
    strokes_.insert({current_color, vector<vector<vec2>>{}});
  }
  strokes_.at(current_color).push_back(points_);

  points_.clear(); // Clear points_ vector
  previous_colors_.push_back(
      current_color); // Update previous colors with current color
}

void Sketchpad::UndoStroke() {
  if (previous_colors_.size() > 0) {
    strokes_.at(previous_colors_.back()).pop_back(); // Update strokes map
    previous_colors_.pop_back(); // Update previous colors vector
  }
}

void Sketchpad::Clear() {
  // Clear strokes_ map, previous_colors_ vector, and points_ vector
  strokes_.clear();
  previous_colors_.clear();
  points_.clear();
}

vector<vec2>& Sketchpad::GetPoints() {
  return points_;
}

vector<string>& Sketchpad::GetColors() {
  return previous_colors_;
}

unordered_map<string, vector<vector<vec2>>>& Sketchpad::GetStrokes() {
  return strokes_;
}

} // namespace visualizer

} // namespace digitaltextconverter
