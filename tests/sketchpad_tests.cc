#include <visualizer/sketchpad.h>
#include <catch2/catch.hpp>

using digitaltextconverter::visualizer::Sketchpad;

using glm::vec2;

using std::string;
using std::vector;

TEST_CASE("Add sketchpad point", "[point-creation]") {
  Sketchpad sketchpad(vec2(100, 100), 800 - 2 * 100);
  sketchpad.HandleBrush(vec2(250, 200));
  vector<vec2> points = sketchpad.GetPoints();

  REQUIRE(points.size() == 41);
  REQUIRE(points[0] == vec2(250, 200));
  REQUIRE(points[1] == vec2(251, 201));
  REQUIRE(points[2] == vec2(249, 201));
  REQUIRE(points[3] == vec2(251, 199));
  REQUIRE(points[4] == vec2(249, 199));
  REQUIRE(points[5] == vec2(251, 200));
  REQUIRE(points[6] == vec2(249, 200));
  REQUIRE(points[7] == vec2(250, 201));
  REQUIRE(points[8] == vec2(250, 199));
}

TEST_CASE("Add sketchpad stroke", "[stroke-creation][previous-colors]") {
  Sketchpad sketchpad(vec2(100, 100), 800 - 2 * 100);
  sketchpad.HandleBrush(vec2(250, 200));
  vector<vec2> points = sketchpad.GetPoints();
  REQUIRE(points.size() == 41);
  vector<string> colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 0);

  sketchpad.UpdateStrokes("white");
  REQUIRE(sketchpad.GetStrokes().size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white").size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white")[0] == points);

  colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 1);
  REQUIRE(colors[0] == "white");

  points = sketchpad.GetPoints();
  REQUIRE(points.size() == 0);
}

TEST_CASE("Undo sketchpad stroke", "[stroke-deletion][previous-colors]") {
  Sketchpad sketchpad(vec2(100, 100), 800 - 2 * 100);
  sketchpad.HandleBrush(vec2(250, 200));
  vector<vec2> points = sketchpad.GetPoints();
  REQUIRE(points.size() == 41);
  vector<string> colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 0);

  sketchpad.UpdateStrokes("white");
  REQUIRE(sketchpad.GetStrokes().size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white").size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white")[0] == points);

  colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 1);
  REQUIRE(colors[0] == "white");

  points = sketchpad.GetPoints();
  REQUIRE(points.size() == 0);

  sketchpad.UndoStroke();
  REQUIRE(sketchpad.GetStrokes().size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white").size() == 0);

  colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 0);
}

TEST_CASE("Clear all sketchpad elements", "[clear-sketchpad][previous-colors]") {
  Sketchpad sketchpad(vec2(100, 100), 800 - 2 * 100);
  sketchpad.HandleBrush(vec2(250, 200));
  vector<vec2> points = sketchpad.GetPoints();
  REQUIRE(points.size() == 41);
  vector<string> colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 0);

  sketchpad.UpdateStrokes("white");
  REQUIRE(sketchpad.GetStrokes().size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white").size() == 1);
  REQUIRE(sketchpad.GetStrokes().at("white")[0] == points);

  colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 1);
  REQUIRE(colors[0] == "white");

  points = sketchpad.GetPoints();
  REQUIRE(points.size() == 0);

  sketchpad.Clear();
  REQUIRE(sketchpad.GetStrokes().size() == 0);

  colors = sketchpad.GetColors();
  REQUIRE(colors.size() == 0);
}
