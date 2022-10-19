#include "util.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "todo_list.hpp"

static TodoItem *parse_line(std::string line, int nline);
static void sort_token(std::string token, TodoItem *item);

void scan_file(std::string path, TodoList *list) {
  std::fstream file;
  std::string line;

  file.open(path);

  if (!file.is_open()) {
    /* TODO: ERROR: could not open file */
    return;
  }

  std::regex type_exp("(TODO|FIXME|NOTE|HACK)(?=:)");

  int nline = 0;
  while (std::getline(file, line)) {
    nline++;
    if (std::regex_search(line, type_exp)) {
      TodoItem *item = parse_line(line, nline);
      item->filepath = path;

      /* add new item to the todo list */
      list->append(item);
    }
  }

  file.close();
}

static TodoItem *parse_line(std::string line, int nline) {
  TodoItem *item = new TodoItem();

  item->nline = nline;

  /* whitespace expression */
  std::regex tk_split("\\s+");

  /* declare iterator to tokenize line according to whitespace */
  auto iter =
      std::sregex_token_iterator(line.begin(), line.end(), tk_split, -1);

  for (iter; iter != std::sregex_token_iterator(); iter++) {
    sort_token(iter->str(), item);
  }

  return item;
}

static void sort_token(std::string token, TodoItem *item) {
  std::regex type_exp("(TODO|FIXME|NOTE|HACK):");

  /* uppercase word followed by colon */
  std::regex is_tag("[A-Z]+:");

  /* c style comments and python comment */
  std::regex is_cmt("(\\/\\/|\\/\\*|\\*\\/|#)");

  if (std::regex_match(token, type_exp)) {
    token.pop_back(); /* remove colon */
    item->type = token;
  } else if (std::regex_match(token, is_tag)) {
    token.pop_back(); /* remove colon */
    item->topics.push_back(token);
  } else if (std::regex_match(token, is_cmt) || token.empty()) {
    /* ignore */
    return;
  } else {
    item->msg.append(token + " ");
  }
}

void write_list_to_file(GentodoData *data) {
  std::ofstream file;

  file.open(data->list_filename);

  if (!file.is_open()) {
    /* TODO: ERROR: Could not open file */
    std::cout << "Could not open file\n";
    return;
  }

  file << data->todo_list->generate_list(data->sort_flag);

  file.close();
  return;
}

void scan_dir(const std::string dir, GentodoData *data) {
  /* Directory iterator */
  for (auto &item : std::filesystem::directory_iterator{dir}) {
    std::string item_path = item.path().string();

    /* If item is in ignore_list, skip */
    if (data->ignore_list->contains(item_path)) {
      continue;
    }

    if (item.is_directory()) {
      scan_dir(item_path, data);
    }

    if (data->file_ext_regex != "") {
      /* Get regex expression from input */
      std::regex exp(data->file_ext_regex);

      std::string ext(item.path().extension());

      if (std::regex_search(ext, exp)) {
        scan_file(item_path, data->todo_list);
      }
    }
  }
}
