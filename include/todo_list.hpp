#ifndef TODOLIST_HPP__
#define TODOLIST_HPP__

#include <string>
#include <unordered_map>
#include <vector>

struct TodoItem {
  /* todo, fixme, hack, note */
  std::string type;

  /* Topics appended to the todo statement. */
  std::vector<std::string> topics;

  /* Message after todo and topics */
  std::string msg;

  /* Path to the file containing the entry */
  std::string filepath;

  /* Line number */
  int nline;
};

enum TodoFlags {
  TODO_SORT_BY_FILE,
  TODO_SORT_BY_TYPE,
  TODO_SORT_BY_TOPIC,
};

class TodoList {
 public:
  TodoList() { /* nothing */
  }
  ~TodoList();

  /* Add new todo entry to the list */
  void append(TodoItem *item);

  /* Generate list */
  const std::string generate_list(TodoFlags flags);

  /* Check if list is empty */
  bool empty() const;

  /* Get number of items in TodoList */
  int size() const;

 private:
  std::vector<TodoItem *> m_items;

  /* Helper fns to sort items */
  void m_group_by_file();  /* Sort by file */
  void m_group_by_type();  /* Sort by type */
  void m_group_by_topic(); /* Sort by topic */

  /* Helper fns to print formatted lists */
  const std::string m_print_by_file() const;  /* Print by file */
  const std::string m_print_by_type() const;  /* Print by type */
  const std::string m_print_by_topic() const; /* Print by topic */

  /* Maps to store sorted items */
  std::unordered_map<std::string, std::vector<TodoItem *>>
      m_grouped_by_file; /* m_grouped_by_file */
  std::unordered_map<std::string, std::vector<TodoItem *>>
      m_grouped_by_type; /* m_grouped_by_type */
  std::unordered_map<std::string, std::vector<TodoItem *>>
      m_grouped_by_topic; /* m_grouped_by_topic */
};

#endif
