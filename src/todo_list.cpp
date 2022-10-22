#include <iostream>
#include <unordered_map>

#include "todo_list.hpp"

TodoList::~TodoList() {
  for (auto item : m_items) {
    free(item);
  }
}

void TodoList::append(TodoItem *item) { m_items.push_back(item); }

bool TodoList::empty() const { return m_items.empty(); }

int TodoList::size() const { return m_items.size(); }

const std::string TodoList::generate_list(TodoFlags flags) {
  ItemTable table;

  switch (flags) {
    case TODO_BY_FILE:
      return m_print_by_file(m_items);
    case TODO_BY_TYPE:
      return m_print_by_type(m_items);
    case TODO_BY_TOPIC:
      return m_print_by_topic(m_items);
  }
}

TodoList::ItemTable TodoList::m_group_by_file(TodoList::ItemList list) {
  ItemTable table;

  for (auto item : list) {
    auto map_iter = table.find(item->filepath);

    if (map_iter == table.end()) { /* group don't exist */
      ItemList t;

      /* Add current item to vector */
      t.push_back(item);

      /* Create mapping */
      table.emplace(item->filepath, t);
    } else { /* group exist */
      /* Add todo item to approprate vector */
      map_iter->second.push_back(item);
    }
  }

  return table;
}

TodoList::ItemTable TodoList::m_group_by_type(TodoList::ItemList list) {
  ItemTable table;

  for (auto item : list) {
    auto map_iter = table.find(item->type);

    if (map_iter == table.end()) { /* group don't exist */
      ItemList t;

      /* Add current item to vector */
      t.push_back(item);

      /* Create mapping */
      table.emplace(item->type, t);
    } else { /* group exist */
      /* Add todo item to approprate vector */
      map_iter->second.push_back(item);
    }
  }

  return table;
}

TodoList::ItemTable TodoList::m_group_by_topic(TodoList::ItemList list) {
  ItemTable table;

  for (auto item : list) {
    if (item->topics.empty()) { /* No topic assigned */
      auto map_iter = table.find("NO TOPIC");

      /* Group exist? */
      if (map_iter == table.end()) { /* group don't exist */
        ItemList t;

        /* Add current item to vector */
        t.push_back(item);

        /* Create mapping */
        table.emplace("NO TOPIC", t);
      } else { /* group exist */
        /* Add todo item to approprate vector */
        map_iter->second.push_back(item);
      }
    } else {
      for (auto topic : item->topics) { /* For each topic assigned to item */
        auto map_iter = table.find(topic);

        /* Group exist? */
        if (map_iter == table.end()) { /* group don't exist */
          ItemList t;

          /* Add current item to vector */
          t.push_back(item);

          /* Create mapping */
          table.emplace(topic, t);
        } else { /* group exist */
          /* Add todo item to approprate vector */
          map_iter->second.push_back(item);
        }
      }
    }
  }

  return table;
}

const std::string TodoList::m_print_by_file(ItemList list) {
  std::vector<std::string> lines;
  lines.push_back("# Todo list\n");

  /* Group by file */
  ItemTable table = m_group_by_file(list);

  for (auto group : table) {
    lines.push_back('`' + group.first + '`');

    /* Group by type */
    ItemTable sub_table = m_group_by_type(group.second);

    for (auto sub_group : sub_table) {
      /* group type */
      lines.push_back("- " + sub_group.first);

      for (auto item : sub_group.second) {
        std::string topics;
        for (auto topic : item->topics) {
          topics += topic + ": ";
        }
        lines.push_back("  - [ ] line " + std::to_string(item->nline) + ": " +
                        topics + item->msg);
      }
    }
    lines.push_back("");
  }
  std::string out;
  for (auto line : lines) {
    out += line + '\n';
  }
  return out;
}

const std::string TodoList::m_print_by_type(ItemList list) {
  std::vector<std::string> lines;
  lines.push_back("# Todo list\n");

  /* Group by file */
  ItemTable table = m_group_by_type(list);

  for (auto group : table) {
    lines.push_back("**" + group.first + "**");

    /* Group by type */
    ItemTable sub_table = m_group_by_file(group.second);

    for (auto sub_group : sub_table) {
      /* group type */
      lines.push_back("- `" + sub_group.first + '`');

      for (auto item : sub_group.second) {
        std::string topics;
        for (auto topic : item->topics) {
          topics += topic + ": ";
        }
        lines.push_back("  - [ ] line " + std::to_string(item->nline) + ": " +
                        topics + item->msg);
      }
    }
    lines.push_back("");
  }
  std::string out;
  for (auto line : lines) {
    out += line + '\n';
  }
  return out;
}

const std::string TodoList::m_print_by_topic(ItemList list) {
  std::vector<std::string> lines;
  lines.push_back("# Todo list\n");

  /* Group by file */
  ItemTable table = m_group_by_topic(list);

  for (auto group : table) {
    lines.push_back("**" + group.first + "**");

    /* Group by type */
    ItemTable sub_table = m_group_by_file(group.second);

    for (auto sub_group : sub_table) {
      /* group type */
      lines.push_back("- `" + sub_group.first + '`');

      for (auto item : sub_group.second) {
        lines.push_back("  - [ ] line " + std::to_string(item->nline) + ": " +
                        item->type + ": " + item->msg);
      }
    }
    lines.push_back("");
  }
  std::string out;
  for (auto line : lines) {
    out += line + '\n';
  }
  return out;
}
