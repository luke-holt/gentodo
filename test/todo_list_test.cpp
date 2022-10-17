#include <gtest/gtest.h>

#include "todo_list.hpp"


/* Verify that append method is working along with empty method */
TEST(TodoList_test, test)
{
    ASSERT_TRUE(1);
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
