#include "cli/command_line_input_parser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using boost::program_options::bool_switch;
using boost::program_options::command_line_parser;
using boost::program_options::notify;
using boost::program_options::options_description;
using boost::program_options::store;
using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::validators::get_single_string;

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

namespace digitaltextconverter {

namespace cli {

UserOptions CommandLineInputParser::ProcessUserOptions() const {
  // Initialize new options struct
  UserOptions user_opts = UserOptions();

  // Populate all options and storage mechanisms
  options_description desc("Allowed User Options");
  desc.add_options()
      ("load", bool_switch(&user_opts.load)->default_value(false), "Standard load user command")
      ("image_path", value<vector<string>>(), "Model input file path")
      ("save", bool_switch(&user_opts.save)->default_value(false), "Standard save user command")
      ("output_file", value<vector<string>>(), "Model output file path")
      ("help","Display possible user options");

  // Build variable map with entered CLI input
  variables_map vm;
  store(command_line_parser(argc_value_, argv_values_).options(desc).run(), vm);
  notify(vm);

  try {
    // Assign image input filepath
    if (user_opts.load) {
      user_opts.image_path =
          get_single_string(vm["image_path"].as<vector<string>>());
      if (!FileExists(user_opts.image_path)) {
        throw std::ifstream::failure("Could not access image input file.");
      }
    }

    // Assign text output filepath
    if (user_opts.save) {
      user_opts.output_file =
          get_single_string(vm["output_file"].as<vector<string>>());
    }

    // Default help commands to display options
    if (vm.count("help")) {
      cout << desc << endl;
      user_opts.exit = true;
      return user_opts;
    }
  } catch (exception &ex) {
    cerr << "Review the valid options below and try again. Remember to provide "
            "valid filepaths. Error: "
         << ex.what() << endl;
    cout << desc << endl;
    user_opts.exit = true;
  }
  return user_opts;
}

/**
 * Checks if a filestream is valid or not.
 * @param filename - filepath to check
 * @return a boolean referring to the validity of the file stream
 */
bool CommandLineInputParser::FileExists(const string filename) const {
  // Concept from:
  // https://stackoverflow.com/questions/27587956/how-to-check-if-a-string-has-a-valid-file-path-or-directory-path-format-in-unman
  std::ifstream test(filename);
  return (test) ? true : false;
}

}  // namespace cli

}  // namespace digitaltextconverter
