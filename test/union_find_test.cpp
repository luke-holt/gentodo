#include "union_find.hpp"

#include <gtest/gtest.h>
#include <sys/wait.h>

TEST(UnionFind, empty) {
  UnionFind<int> uf{};

  ASSERT_TRUE(uf.empty());

  uf.add_item("1", 1);

  ASSERT_FALSE(uf.empty());

  uf.add_item("2", 2);

  ASSERT_FALSE(uf.empty());
}

TEST(UnionFind, size) {
  UnionFind<int> uf{};

  ASSERT_EQ(uf.size(), 0);

  uf.add_item("1", 1);

  ASSERT_EQ(uf.size(), 1);

  uf.add_item("2", 2);

  ASSERT_EQ(uf.size(), 2);

  uf.add_item("3", 3);
  uf.add_item("4", 4);
  uf.add_item("5", 5);
  uf.add_item("6", 6);

  ASSERT_EQ(uf.size(), 6);
}

TEST(UnionFind, get_items) {
  UnionFind<int> uf{};

  ASSERT_TRUE(uf.get_items().empty());

  uf.add_item("1", 1);
  uf.add_item("2", 2);
  uf.add_item("3", 3);

  /* For strings "1", "2", "3", inserted into an unordered map,
   * the order is 2, 3, 1 */
  std::vector<int> x{2, 3, 1};

  std::vector<int> items = uf.get_items();

  ASSERT_EQ(x[0], items[0]);
  ASSERT_EQ(x[1], items[1]);
  ASSERT_EQ(x[2], items[2]);
}

/* TODO: TEST: Add test for union-find algorithm */
