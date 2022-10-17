#include <map>

#include "todo_list.hpp"

/*
static void union();
static int find();
*/


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


bool TodoList::empty()
{
    return m_items.empty();
}


const std::string TodoList::generate_list(TodoFlags flags)
{
    std::map<std::string, std::vector<TodoItem*>> *selected_map;

    switch (flags) {
    case TODO_SORT_BY_FILE:
        sort_by_file();
        selected_map = &m_sorted_by_file;
        break;
    case TODO_SORT_BY_TYPE:
        sort_by_type();
        selected_map = &m_sorted_by_type;
        break;
    case TODO_SORT_BY_TOPIC:
        sort_by_topic();
        selected_map = &m_sorted_by_topic;
        break;
    }


    /* Print items into string */
    std::string out;
    for (auto group : *selected_map) {
        out += group.first + " :\n";
        for (auto item : group.second) {
            out += item->type + ": ";
            for (auto topic : item->topics) out += topic + ": ";
            out += item->msg + '\n';
        }
        out += '\n';
    }

    return out;
}


void TodoList::sort_by_file()
{
    /* Sort items */
    for (auto item : m_items) {
        auto map_iter = m_sorted_by_file.find(item->filepath);

        /* Group exist? */
        if (map_iter == m_sorted_by_file.end()) { /* group don't exist */
            std::vector<TodoItem*> t;

            /* Add current item to vector */
            t.push_back(item);

            /* Create mapping */
            m_sorted_by_file.emplace(item->filepath, t);
        }
        else { /* group exist */
            /* Add todo item to approprate vector */
            map_iter->second.push_back(item);
        }
    }
}


void TodoList::sort_by_type()
{
    /* Sort items */
    for (auto item : m_items) {
        auto map_iter = m_sorted_by_type.find(item->type);

        /* Group exist? */
        if (map_iter == m_sorted_by_type.end()) { /* group don't exist */
            std::vector<TodoItem*> t;

            /* Add current item to vector */
            t.push_back(item);

            /* Create mapping */
            m_sorted_by_type.emplace(item->type, t);
        }
        else { /* group exist */
            /* Add todo item to approprate vector */
            map_iter->second.push_back(item);
        }
    }
}


void TodoList::sort_by_topic()
{
    /* Sort items */
    for (auto item : m_items) {
        if (item->topics.empty()) { /* No topic assigned */
            auto map_iter = m_sorted_by_topic.find("NO_TOPIC");

            /* Group exist? */
            if (map_iter == m_sorted_by_topic.end()) { /* group don't exist */
                std::vector<TodoItem*> t;

                /* Add current item to vector */
                t.push_back(item);

                /* Create mapping */
                m_sorted_by_topic.emplace("NO_TOPIC", t);
            }
            else { /* group exist */
                /* Add todo item to approprate vector */
                map_iter->second.push_back(item);
            }
        }
        else {
            for (auto topic : item->topics) { /* For each topic assigned to item */
                auto map_iter = m_sorted_by_topic.find(topic);

                /* Group exist? */
                if (map_iter == m_sorted_by_topic.end()) { /* group don't exist */
                    std::vector<TodoItem*> t;

                    /* Add current item to vector */
                    t.push_back(item);

                    /* Create mapping */
                    m_sorted_by_topic.emplace(topic, t);
                }
                else { /* group exist */
                    /* Add todo item to approprate vector */
                    map_iter->second.push_back(item);
                }
            }
        }
    }
}
