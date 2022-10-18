#ifndef UNIONFIND_HPP__
#define UNIONFIND_HPP__

#include <string>
#include <unordered_map>
#include <vector>

template <typename T>

class UnionFind {
 public:
  /* Find operation in Union-Find algorithm */
  T find(std::string s) {
    /* String for path compression */
    std::string path_cmp_str = s;

    while (m_parent[s] != s) s = m_parent[s];

    /* Path compression */
    while (path_cmp_str != s) {
      std::string tmp = m_parent[path_cmp_str];
      m_parent[path_cmp_str] = s;
      path_cmp_str = tmp;
    }

    return s;
  }

  /* Union operation in Union-Find algorithm */
  void unify(std::string s1, std::string s2) {
    std::string root_s1 = find(s1);
    std::string root_s2 = find(s2);

    if (root_s1 == root_s2) return;

    /* Unify smaller component to larger component */
    if (m_size[root_s1] < m_size[root_s2]) {
      m_parent[root_s1] = root_s2;
      m_size[root_s2] += m_size[root_s1];
    } else {
      m_parent[root_s2] = root_s1;
      m_size[root_s1] += m_size[root_s2];
    }
  }

  /* Add item to class contents */
  void add_item(std::string str, T item) {
    m_size.emplace(str, 1);
    m_parent.emplace(str, item);
  }

  /* Returns vector containing all items added to class */
  std::vector<T> get_items() const {
    std::vector<T> out;

    for (auto item : m_parent) {
      out.push_back(item.second);
    }

    return out;
  }

  bool empty() const { return m_parent.empty(); }

  int size() const { return m_parent.size(); }

 private:
  std::unordered_map<std::string, int> m_size;
  std::unordered_map<std::string, T> m_parent;
};

#endif
