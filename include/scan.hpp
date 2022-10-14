#ifndef UTIL_HPP__
#define UTIL_HPP__

#include <filesystem>

#include "todo_list.hpp"

void scan_file(std::string path, TodoList *list);

#endif
