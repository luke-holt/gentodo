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
  std::regex valid_file_regex("^[a-zA-Z0-9]+\\.?[a-zA-Z0-9]+$");

  /* Object to be passed around */
  GentodoData gentodo_data = {
      .ignore_list = new IgnoreList(".gentodoignore"),
      .todo_list = new TodoList(),
      .list_filename = "TODO.md", /* Default filename */
  };

  for (;;) {
    ret_val = getopt(argc, argv, "e:s:o:h");

    if (ret_val == -1) {
      break;
    }

    switch (ret_val) {
      case 'e': /* Regex expression to match file extensions to scan */
        gentodo_data.file_ext_regex = optarg;
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

      case 'o': /* output name */
        if (std::regex_match(optarg, valid_file_regex)) {
          gentodo_data.list_filename = optarg;
        } else {
          fprintf(stderr, "Invalid filename, see help for details.");
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

  scan_dir(".", &gentodo_data);

  write_list_to_file(&gentodo_data);

  return 0;
}

static void print_help() {
  /* TODO: CMDLN: Add help message */
  std::cout << "Help msg\n";
}
