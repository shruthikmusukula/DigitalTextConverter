#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

using std::string;
using std::unordered_map;
using std::vector;

namespace digitaltextconverter {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class Sketchpad {
public:
  /**
   * Creates a sketchpad.
   * (Note that sketchpad pixels are larger than screen pixels.)
   *
   * @param top_left_corner     the screen coordinates of the top left corner of
   *                            the sketchpad
   * @param sketchpad_size      the side length of the sketchpad, measured in
   *                            screen pixels
   */
  Sketchpad(const glm::vec2 &top_left_corner, double sketchpad_size);
  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw(string color);
  /**
   * Adds user-drawn coordinate points to the sketchpad.
   * @param point_coords the screen coordinates at which the brush is
   *           located
   */
  void HandleBrush(const vec2 &point_coords);
  /**
   * Adds latest user stroke to strokes map and updates previous colors.
   * @param current_color - The current color to add to previous colors.
   */
  void UpdateStrokes(const string current_color);
  /**
   * Deletes latest entry from previous colors and strokes map.
   */
  void UndoStroke();
  /**
   * Set all of the sketchpad pixels to an unshaded state.
   */
  void Clear();
  /**
   * Get all filled points on the sketchpad.
   * @return the current points vector
   */
  vector<vec2>& GetPoints();
  /**
   * Get all previous colors on the sketchpad.
   * @return the previous colors vector
   */
  vector<string>& GetColors();
  /**
   * Get all strokes on the sketchpad.
   * @return the current strokes map
   */
  unordered_map<string, vector<vector<vec2>>>& GetStrokes();

private:
  /** Thickness of user's brush */
  const size_t kBrushSize = 5;
  /** Standard container line width */
  static constexpr double kLineWidth = 3.5;
  /** Size of the simulation board */
  double side_length_;
  /** Coordinates of the top left corner of the sketchpad */
  glm::vec2 top_left_corner_;
  /** Map or user strokes from color to vector of points */
  unordered_map<string, vector<vector<vec2>>> strokes_;
  /** Previous colors of each stroke in order */
  vector<string> previous_colors_;
  /** Points in current user stroke */
  vector<vec2> points_;
};

} // namespace visualizer

} // namespace digitaltextconverter
