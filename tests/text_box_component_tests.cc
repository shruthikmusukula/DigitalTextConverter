#include <visualizer/text_box_component.h>
#include <catch2/catch.hpp>

using digitaltextconverter::visualizer::TextBoxComponent;

using std::string;

TEST_CASE("Setup text box component", "[setup]") {
  TextBoxComponent tb;
  tb.Setup();
  REQUIRE(tb.GetText().size() == 0);
}

TEST_CASE("Set text box component content", "[set-text]") {
  TextBoxComponent tb;
  tb.Setup();
  REQUIRE(tb.GetText().size() == 0);

  tb.SetText("text");
  REQUIRE(tb.GetText().size() == 4);
  REQUIRE(tb.GetText() == "text");
}

TEST_CASE("Delete last character in text box component", "[delete-last-char]") {
  SECTION("Delete last character with non-empty text content") {
    TextBoxComponent tb;
    tb.Setup();
    REQUIRE(tb.GetText().size() == 0);

    tb.SetText("text");
    REQUIRE(tb.GetText().size() == 4);
    REQUIRE(tb.GetText() == "text");

    tb.DeleteChar();
    REQUIRE(tb.GetText().size() == 0);
  }

  SECTION("Delete last character with empty text content") {
    TextBoxComponent tb;
    tb.Setup();
    REQUIRE(tb.GetText().size() == 0);

    tb.DeleteChar();
    REQUIRE(tb.GetText().size() == 0);
  }
}
