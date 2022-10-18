#ifndef UTIL_HPP__
#define UTIL_HPP__

#include <filesystem>
#include <string>

#include "todo_list.hpp"

void scan_file(std::string path, TodoList *list);

void write_list_to_file(const std::string markdown_list, const std::string filename);

#endif
