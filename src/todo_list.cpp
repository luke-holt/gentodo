#include "todo_list.hpp"

#include <iostream>
#include <unordered_map>

#include "union_find.hpp"

TodoList::~TodoList() {
  for (auto item : m_items) {
    free(item);
  }
}

void TodoList::append(TodoItem *item) { m_items.push_back(item); }

bool TodoList::empty() const { return m_items.empty(); }

int TodoList::size() const { return m_items.size(); }

const std::string TodoList::generate_list(TodoFlags flags) {
  std::unordered_map<std::string, std::vector<TodoItem *>> *selected_map;

  switch (flags) {
    case TODO_SORT_BY_FILE:
      m_group_by_file();
      selected_map = &m_grouped_by_file;
      break;
    case TODO_SORT_BY_TYPE:
      m_group_by_type();
      selected_map = &m_grouped_by_type;
      break;
    case TODO_SORT_BY_TOPIC:
      m_group_by_topic();
      selected_map = &m_grouped_by_topic;
      break;
  }

  if (selected_map->empty()) {
    return "There are no tasks left to do :)";
  }

  /* Print items into string */
  std::vector<std::string> col1;
  int col1_max_len = 0;
  std::vector<std::string> col2;
  int col2_max_len = 0;
  std::vector<std::string> col3;
  int col3_max_len = 0;
  std::vector<std::string> col4;

  auto ceil = [](int a, int b) { return (a > b) ? a : b; };

  for (auto group : *selected_map) {
    for (auto item : group.second) {
      col1.push_back(group.first);
      col1_max_len = ceil((int)(group.first.size()), col1_max_len);

      col2.push_back(item->type);
      col2_max_len = ceil((int)(item->type.size()), col2_max_len);

      for (auto topic : item->topics) {
        col3.push_back(topic);
        col3_max_len = ceil((int)(topic.size()), col3_max_len);
      }
      if (col3.empty()) {
        col3.push_back("");
      }

      col4.push_back(item->msg);
    }
  }

  /* lambda to insert appropriate number of spaces to align columns */
  auto diff = [](std::string in, int max_len) {
    std::string out;
    int x = (8 - (max_len % 4) + (max_len - (int)(in.size())));
    for (int i = 0; i < x; i++) out += ' ';
    return out;
  };

  std::string out;
  for (int i = 0; i < (int)col1.size(); i++) {
    out += col1[i];
    out += diff(col1[i], col1_max_len);

    out += col2[i];
    out += diff(col2[i], col2_max_len);

    out += col3[i];
    out += diff(col3[i], col3_max_len);

    out += col4[i] + '\n';
  }
  out += '\n';

  return out;
}

void TodoList::m_group_by_file() {
  /* Sort items */
  for (auto item : m_items) {
    auto map_iter = m_grouped_by_file.find(item->filepath);

    /* Group exist? */
    if (map_iter == m_grouped_by_file.end()) { /* group don't exist */
      std::vector<TodoItem *> t;

      /* Add current item to vector */
      t.push_back(item);

      /* Create mapping */
      m_grouped_by_file.emplace(item->filepath, t);
    } else { /* group exist */
      /* Add todo item to approprate vector */
      map_iter->second.push_back(item);
    }
  }
}

void TodoList::m_group_by_type() {
  /* Sort items */
  for (auto item : m_items) {
    auto map_iter = m_grouped_by_type.find(item->type);

    /* Group exist? */
    if (map_iter == m_grouped_by_type.end()) { /* group don't exist */
      std::vector<TodoItem *> t;

      /* Add current item to vector */
      t.push_back(item);

      /* Create mapping */
      m_grouped_by_type.emplace(item->type, t);
    } else { /* group exist */
      /* Add todo item to approprate vector */
      map_iter->second.push_back(item);
    }
  }
}

void TodoList::m_group_by_topic() {
  /* Sort items */
  for (auto item : m_items) {
    if (item->topics.empty()) { /* No topic assigned */
      auto map_iter = m_grouped_by_topic.find("NO_TOPIC");

      /* Group exist? */
      if (map_iter == m_grouped_by_topic.end()) { /* group don't exist */
        std::vector<TodoItem *> t;

        /* Add current item to vector */
        t.push_back(item);

        /* Create mapping */
        m_grouped_by_topic.emplace("NO_TOPIC", t);
      } else { /* group exist */
        /* Add todo item to approprate vector */
        map_iter->second.push_back(item);
      }
    } else {
      for (auto topic : item->topics) { /* For each topic assigned to item */
        auto map_iter = m_grouped_by_topic.find(topic);

        /* Group exist? */
        if (map_iter == m_grouped_by_topic.end()) { /* group don't exist */
          std::vector<TodoItem *> t;

          /* Add current item to vector */
          t.push_back(item);

          /* Create mapping */
          m_grouped_by_topic.emplace(topic, t);
        } else { /* group exist */
          /* Add todo item to approprate vector */
          map_iter->second.push_back(item);
        }
      }
    }
  }
}

/* TODO: TODOLIST: Write these methods */

const std::string TodoList::m_print_by_file() const { return "TODO"; }

const std::string TodoList::m_print_by_type() const { return "TODO"; }

const std::string TodoList::m_print_by_topic() const { return "TODO"; }
