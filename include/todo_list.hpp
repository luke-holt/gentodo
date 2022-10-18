#ifndef TODOLIST_HPP__
#define TODOLIST_HPP__

#include <string>
#include <vector>
#include <filesystem>
#include <map>


struct TodoItem
{
    /* todo, fixme, hack, note */
    std::string type;

    /* Topics appended to the todo statement. */
    std::vector<std::string> topics;

    /* Message after todo and topics */
    std::string msg;

    /* Path to the file containing the entry */
    std::filesystem::path filepath;

    /* Line number */
    int nline;
};


enum TodoFlags {
    TODO_SORT_BY_FILE,
    TODO_SORT_BY_TYPE,
    TODO_SORT_BY_TOPIC,
};


class TodoList
{
public:
    TodoList() { /* nothing */ }
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
    std::vector<TodoItem*> m_items;

    /* Helper fns to sort items */
    void m_sort_by_file(); /* Sort by file */
    void m_sort_by_type(); /* Sort by type */
    void m_sort_by_topic(); /* Sort by topic */

    /* Maps to store sorted items */
    std::map<std::string, std::vector<TodoItem*>> m_sorted_by_file; /* m_sorted_by_file */
    std::map<std::string, std::vector<TodoItem*>> m_sorted_by_type; /* m_sorted_by_type */
    std::map<std::string, std::vector<TodoItem*>> m_sorted_by_topic; /* m_sorted_by_topic */
};

#endif

