#ifndef IGNORELIST_HPP__
#define IGNORELIST_HPP__

#include <string>
#include <vector>

class IgnoreList {
 public:
  IgnoreList();
  ~IgnoreList(){/* nothing */};

  bool contains(std::string file) const;

  const std::string contents() const;

 private:
  std::vector<std::string> m_items;
};

#endif
