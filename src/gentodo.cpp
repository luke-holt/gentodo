#include <getopt.h>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "ignore_list.hpp"
#include "todo_list.hpp"
#include "util.hpp"

static void print_help();

int main(int argc, char *argv[]) {
  int ret_val;
  int fflag = 0;
  int dflag = 0;
  int oflag = 0;

  std::regex valid_path_regex(
      "^[a-zA-Z0-9\\_/\\.][a-zA-Z0-9\\_\\-/]+\\.?[a-zA-Z0-9\\_\\-]+$");

  /* Object to be passed around */
  GentodoData gentodo_data = {
      .ignore_list = new IgnoreList(),
      .todo_list = new TodoList(),
  };

  for (;;) {
    ret_val = getopt(argc, argv, "d:e:f:ho:s:");

    if (ret_val == -1) {
      break;
    }

    switch (ret_val) {
      case 'd': /* Directory to scan */
        if (std::regex_match(optarg, valid_path_regex)) {
          gentodo_data.path = optarg;
        } else {
          fprintf(stderr, "Invalid filename, see help for details.");
          return -1;
        }
        dflag = 1;
        break;

      case 'e': /* Regex expression to match file extensions to scan */
        gentodo_data.file_ext_regex = optarg;
        break;

      case 'f':
        if (std::regex_match(optarg, valid_path_regex)) {
          gentodo_data.ignore_list->load(optarg);
        } else {
          fprintf(stderr, "Invalid filename, see help for details.");
          return -1;
        }
        fflag = 1;
        break;

      case 'o': /* output name */
        if (std::regex_match(optarg, valid_path_regex)) {
          gentodo_data.list_filename = optarg;
        } else {
          fprintf(stderr, "Invalid filename, see help for details.");
          return -1;
        }
        oflag = 1;
        break;

      case 's': /* Sort by */
        if (strcmp(optarg, "file") == 0) {
          gentodo_data.sort_flag = TODO_BY_FILE;
        } else if (strcmp(optarg, "type") == 0) {
          gentodo_data.sort_flag = TODO_BY_TYPE;
        } else if (strcmp(optarg, "topic") == 0) {
          gentodo_data.sort_flag = TODO_BY_TOPIC;
        } else {
          fprintf(stderr,
                  "Invalid option to sort-by. Must be either 'file', 'type' or "
                  "'topic'.");
          return -1;
        }
        break;

      case '?':
      case 'h':
      default:
        print_help();
        break;
    }
  }

  if (!dflag) {
    gentodo_data.path = ".";
  }
  if (!fflag) {
    gentodo_data.ignore_list->load(".gentodoignore");
  }
  if (!oflag) {
    gentodo_data.list_filename = "./todo.md";
  }

  scan_dir(gentodo_data.path, &gentodo_data);

  write_list_to_file(&gentodo_data);

  return 0;
}

static void print_help() {
  std::cout << "Usage: gentodo [--help] [-e <regex>] [-f <ignore-path>]\n";
  std::cout << "               [-o <output-path] [-s <sort-by>]\n";
  std::cout << '\n';
  std::cout << "Generate a todo list from TODO comments in a directory.\n";
  std::cout << '\n';
  std::cout << " --help        Show this message.\n";
  std::cout << " -e <regex>    Set the regex string to use to search for files "
               "to scan.\n";
  std::cout << " -f <path>     Set the .gentodoignore file used as a list of "
               "items in\n";
  std::cout << "               the target directory to ignore.\n";
  std::cout << " -o <path>     Set output file.\n";
  std::cout << " -s <sort-by>  Specify how the output list should be sorted.\n";
  std::cout << "               Avalable options are: \"file\", \"type\", "
               "\"topic\".\n";
  std::cout << '\n';
}
