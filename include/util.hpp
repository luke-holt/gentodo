#ifndef UTIL_HPP__
#define UTIL_HPP__

#include <filesystem>
#include <string>

#include "ignore_list.hpp"
#include "todo_list.hpp"

struct GentodoData {
  IgnoreList *ignore_list;
  TodoList *todo_list;
  std::string file_ext_regex;
  std::string list_filename;
  TodoFlags sort_flag;
};

void scan_dir(const std::string dir, GentodoData *data);

void scan_file(std::string path, TodoList *list);

void write_list_to_file(GentodoData *data);

#endif
