
#include "todo_list.hpp"

static void union();
static int find();



TodoList::~TodoList()
{
    for (auto item : m_items) {
        free(item);
    }
}

void TodoList::append(TodoItem *item)
{
    m_items.push_back(item);
}


const std::string TodoList::list_by_topic() const
{

    return "list by topic";
}



const std::string TodoList::list_by_type() const
{

    return "list by type";
}



const std::string TodoList::list_by_file() const
{
    /* TODO: ALGO: Union-find? */
    std::vector<int> bijection;

    return "list by file";
}
