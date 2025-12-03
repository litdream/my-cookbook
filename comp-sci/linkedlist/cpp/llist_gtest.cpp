#include "gtest/gtest.h"
#include "llist.hpp"

// Test fixture for LList tests
class LListTest : public ::testing::Test {
protected:
    LList list;
};

// Test case to check if a new list is empty and has a size of 0
TEST_F(LListTest, InitialSizeIsZero) {
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Test case to check if the size is correctly updated after adding elements
TEST_F(LListTest, AddIncrementsSize) {
    list.add(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());

    list.add(20);
    EXPECT_EQ(list.size(), 2);

    list.add(30);
    EXPECT_EQ(list.size(), 3);
}

// Test case to verify that getAt() retrieves the correct values
TEST_F(LListTest, GetReturnsCorrectValue) {
    list.add(100);
    list.add(200);
    list.add(300);

    EXPECT_EQ(list.getAt(0), 100);
    EXPECT_EQ(list.getAt(1), 200);
    EXPECT_EQ(list.getAt(2), 300);
}

// Test case for out-of-bounds access
TEST_F(LListTest, GetThrowsForOutOfBounds) {
    list.add(5);
    // C++ exceptions with gtest require EXPECT_THROW
    EXPECT_THROW(list.getAt(1), std::out_of_range);
    EXPECT_THROW(list.getAt(-1), std::out_of_range);
}
