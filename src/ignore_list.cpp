#include <iostream>
#include <fstream>
#include <sstream>

#include "ignore_list.hpp"


IgnoreList::IgnoreList()
{
    std::ifstream ignore_fs{ ".gentodoignore" };
    std::string line;

    if (ignore_fs.is_open()) {
        while (std::getline(ignore_fs, line)) {
            if (line.empty()) continue;

            if (line.back() == '/') line.pop_back();

            m_items.push_back(line);
        }
    } else {
        std::cout << "Could not find ignore file\n";
    }
}


const std::string IgnoreList::contents() const
{
    std::string contents;

    for (auto& item : m_items) {
        contents += item;
        contents += "\n";
    }

    return contents;
}


bool IgnoreList::contains(std::string file) const
{
    for (auto& item : m_items) {
        std::size_t found = item.find(file);
        if (found != std::string::npos) {
            return true;
        }
    }
    return false;
}

