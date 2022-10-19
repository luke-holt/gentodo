#ifndef TODOLIST_HPP__
#define TODOLIST_HPP__

#include <map>
#include <string>
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
  TODO_BY_FILE,
  TODO_BY_TYPE,
  TODO_BY_TOPIC,
};

class TodoList {
 public:
  TodoList() { /* nothing */
  }
  ~TodoList();

  /* List of TodoItems */
  typedef std::vector<TodoItem *> ItemList;
  /* Table that is used to map a string to a corresponding ItemList */
  typedef std::map<std::string, ItemList> ItemTable;

  /* Add new todo entry to the list */
  void append(TodoItem *item);

  /* Generate list */
  const std::string generate_list(TodoFlags flags);

  /* Check if list is empty */
  bool empty() const;

  /* Get number of items in TodoList */
  int size() const;

 private:
  ItemList m_items;

  /* Helper fns to sort items */
  static ItemTable m_group_by_file(ItemList list);  /* Sort by file */
  static ItemTable m_group_by_type(ItemList list);  /* Sort by type */
  static ItemTable m_group_by_topic(ItemList list); /* Sort by topic */

  /* Helper fns to print formatted lists */
  static const std::string m_print_by_file(ItemList list);  /* Print by file */
  static const std::string m_print_by_type(ItemList list);  /* Print by type */
  static const std::string m_print_by_topic(ItemList list); /* Print by topic */
};

#endif
