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

static int mm_monkey(TodoFlags flags, std::string ext_regex) {
  /* Calling constructor searches for .gentodoignore in current dir "." */
  IgnoreList ignore_list{};

  TodoList list{};

  /* loop through items directory */
  for (auto &item : std::filesystem::directory_iterator{"./src"}) {
    /* if item is in ignore_list, skip */
    if (ignore_list.contains(item.path().filename().string())) {
      continue;
    }

    /* if item is directory, recurse */
    if (item.is_directory()) {
      /* TODO: Iterate into directory */
      continue;
    }

    if (ext_regex != "") {
      /* Get regex expression from input */
      std::regex exp(ext_regex);

      std::string ext(item.path().extension());

      if (std::regex_match(ext, exp)) {
        scan_file(item.path(), &list);
      }
    }

    scan_file(item.path(), &list);
  }

  write_list_to_file(list.generate_list(flags), "./TODO.md");

  return 0;
}

int main(int argc, char *argv[]) {
  /* Options */
  /* -s (file|type|topic) */
  /* -e regex */

  char *ext_regex;
  TodoFlags sort_opt;

  int ret_val;

  for (;;) {
    ret_val = getopt(argc, argv, "e:s:h");

    if (ret_val == -1) {
      break;
    }

    switch (ret_val) {
      case 'e': /* Extensions regex */
        ext_regex = optarg;
        break;

      case 's': /* Sort by */
        if (strcmp(optarg, "file") == 0) {
          sort_opt = TODO_BY_FILE;
        } else if (strcmp(optarg, "type") == 0) {
          sort_opt = TODO_BY_TYPE;
        } else if (strcmp(optarg, "topic") == 0) {
          sort_opt = TODO_BY_TOPIC;
        } else {
          fprintf(
              stderr,
              "Invalid option to sort-by. Must be either file, type or topic");
          return -1;
        }
        break;

      case '?':
      case 'h':
        /* TODO: CMDLN: Add help message */
        std::cout << "I cannot help you, my child.\n";
      default:
        fprintf(stdout, "mm monkey\n");
        break;
    }
  }

  return mm_monkey(sort_opt, ext_regex);
}
