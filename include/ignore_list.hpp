#ifndef IGNORELIST_HPP__
#define IGNORELIST_HPP__

#include <string>
#include <vector>

class IgnoreList {
 public:
  IgnoreList(){/*nothing */};
  IgnoreList(const std::string ignore_path);
  ~IgnoreList(){/* nothing */};

  /* Load contents of .gentodoignore into m_items */
  void load(const std::string ignore_path);

  bool contains(const std::string file) const;

  const std::string contents() const;

 private:
  std::vector<std::string> m_items;
};

#endif
