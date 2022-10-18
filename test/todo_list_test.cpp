#include "todo_list.hpp"

#include <gtest/gtest.h>

/* Verify that append method is working along with empty method */
TEST(TodoList, empty) {
  TodoList list{};
  TodoItem *i = new TodoItem;

  ASSERT_TRUE(list.empty());

  list.append(i);

  ASSERT_FALSE(list.empty());
}

TEST(TodoList, size) {
  TodoList list{};
  TodoItem *i1 = new TodoItem;
  TodoItem *i2 = new TodoItem;
  TodoItem *i3 = new TodoItem;
  TodoItem *i4 = new TodoItem;

  ASSERT_EQ(list.size(), 0);

  list.append(i1);

  ASSERT_EQ(list.size(), 1);

  list.append(i2);
  list.append(i3);
  list.append(i4);

  ASSERT_EQ(list.size(), 4);
}

/* TODO: TODOLIST: Test the generate_list function */

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
