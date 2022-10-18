#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "ignore_list.hpp"
#include "todo_list.hpp"
#include "util.hpp"

int main(/* int argc, char *argv[] */) {
  /* Calling constructor searches for .gentodoignore in current dir "." */
  IgnoreList ignore_list{};

  TodoList list{};

  /* loop through items directory */
  for (auto& item : std::filesystem::directory_iterator{"./src"}) {
    /* if item is in ignore_list, skip */
    if (ignore_list.contains(item.path().filename().string())) {
      continue;
    }

    /* if item is directory, recurse */
    if (item.is_directory()) {
      /* TODO: this */
      continue;
    }

    scan_file(item.path(), &list);
  }

  write_list_to_file(list.generate_list(TODO_SORT_BY_FILE), "./list_by_file.txt");
  write_list_to_file(list.generate_list(TODO_SORT_BY_TYPE), "./list_by_type.txt");
  write_list_to_file(list.generate_list(TODO_SORT_BY_TOPIC), "./list_by_topic.txt");

  return 0;
}
