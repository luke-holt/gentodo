#ifndef TODOLIST_HPP__
#define TODOLIST_HPP__

#include <string>
#include <vector>
#include <filesystem>


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


class TodoList
{
public:
    TodoList() { /* nothing */ }
    ~TodoList();

    /* Add new todo entry to the list */
    void append(TodoItem *item);

    /* Return a formatted list sorted by topic */
    const std::string list_by_topic() const;

    /* Return a formatted list sorted by type */
    const std::string list_by_type() const;

    /* Return a formatted list sorted by file */
    const std::string list_by_file() const;

private:
    std::vector<TodoItem*> m_items;
};

#endif
