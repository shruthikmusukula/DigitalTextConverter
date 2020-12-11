#pragma once

#include <boost/program_options.hpp>
#include <string>

namespace digitaltextconverter {

namespace cli {

/**
 * This struct represents possible arguments from CLI input.
 */
struct UserOptions {
  bool load;
  std::string image_path;
  bool save;
  std::string output_file;
  bool exit = false;
};

/**
 * This class contains logic for representing passed-in
 * CLI arguments and processing them with boost::program_options.
 */
class CommandLineInputParser {
public:
  /** Default constructor for CLI Parser class */
  CommandLineInputParser(const int argc, const char** argv)
      : argc_value_(argc), argv_values_(argv){};
  /** Contains user options */
  UserOptions options;
  /**
   * Evaluates CLI input and updates options as necessary.
   * @return a UserOptions struct to load into options.
   */
  UserOptions ProcessUserOptions() const;

private:
  /** Argc passed in from main */
  const int argc_value_;
  /** Argv passed in from main */
  const char** argv_values_;
  /**
   * Checks whether a given filepath exists.
   * @param filename - filepath to check.
   * @return a boolean referring to whether or not the filepath is valid
   */
  bool FileExists(const std::string filename) const;
};

}  // namespace cli

}  // namespace digitaltextconverter
