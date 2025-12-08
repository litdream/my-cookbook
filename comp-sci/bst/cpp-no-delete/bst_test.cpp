#include "bst.hpp"
#include <gtest/gtest.h>

class BSTTest : public ::testing::Test {
protected:
    BST bst;
};

// Test basic insertion
TEST_F(BSTTest, InsertSingleElement) {
    EXPECT_TRUE(bst.insert(50));
    EXPECT_TRUE(bst.exists(50));
}

// Test insertion of multiple elements
TEST_F(BSTTest, InsertMultipleElements) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int val : values) {
        EXPECT_TRUE(bst.insert(val));
    }

    for (int val : values) {
        EXPECT_TRUE(bst.exists(val));
    }
}

// Test duplicate insertion returns false
TEST_F(BSTTest, InsertDuplicateReturnsFalse) {
    EXPECT_TRUE(bst.insert(50));
    EXPECT_FALSE(bst.insert(50));
    EXPECT_TRUE(bst.exists(50));
}

// Test exists for non-existent element
TEST_F(BSTTest, ExistsReturnsFalseForNonExistent) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);

    EXPECT_FALSE(bst.exists(100));
    EXPECT_FALSE(bst.exists(25));
    EXPECT_FALSE(bst.exists(0));
}

// Test exists on empty tree
TEST_F(BSTTest, ExistsOnEmptyTree) {
    EXPECT_FALSE(bst.exists(42));
}

// Test minimum value
TEST_F(BSTTest, MinimumValue) {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10};

    for (int val : values) {
        bst.insert(val);
    }

    EXPECT_EQ(bst.minimum(), 10);
}

// Test maximum value
TEST_F(BSTTest, MaximumValue) {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 90};

    for (int val : values) {
        bst.insert(val);
    }

    EXPECT_EQ(bst.maximum(), 90);
}

// Test minimum with single element
TEST_F(BSTTest, MinimumSingleElement) {
    bst.insert(42);
    EXPECT_EQ(bst.minimum(), 42);
}

// Test maximum with single element
TEST_F(BSTTest, MaximumSingleElement) {
    bst.insert(42);
    EXPECT_EQ(bst.maximum(), 42);
}

// Test height of empty tree
TEST_F(BSTTest, HeightEmptyTree) {
    EXPECT_EQ(bst.height(), -1);
}

// Test height of single node
TEST_F(BSTTest, HeightSingleNode) {
    bst.insert(50);
    EXPECT_EQ(bst.height(), 0);
}

// Test height of balanced tree
TEST_F(BSTTest, HeightBalancedTree) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    EXPECT_EQ(bst.height(), 1);

    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    EXPECT_EQ(bst.height(), 2);
}

// Test height of left-skewed tree
TEST_F(BSTTest, HeightLeftSkewed) {
    bst.insert(50);
    bst.insert(40);
    bst.insert(30);
    bst.insert(20);
    EXPECT_EQ(bst.height(), 3);
}

// Test height of right-skewed tree
TEST_F(BSTTest, HeightRightSkewed) {
    bst.insert(10);
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    EXPECT_EQ(bst.height(), 3);
}

// Test insertion order independence for existence
TEST_F(BSTTest, InsertionOrderIndependence) {
    BST bst1, bst2;

    int values1[] = {50, 30, 70, 20, 40};
    int values2[] = {30, 50, 20, 70, 40};

    for (int val : values1) {
        bst1.insert(val);
    }

    for (int val : values2) {
        bst2.insert(val);
    }

    for (int val : values1) {
        EXPECT_TRUE(bst1.exists(val));
        EXPECT_TRUE(bst2.exists(val));
    }

    EXPECT_EQ(bst1.minimum(), bst2.minimum());
    EXPECT_EQ(bst1.maximum(), bst2.maximum());
}

// Test with negative numbers
TEST_F(BSTTest, NegativeNumbers) {
    int values[] = {0, -50, 50, -30, 30, -70, 70};

    for (int val : values) {
        EXPECT_TRUE(bst.insert(val));
    }

    EXPECT_EQ(bst.minimum(), -70);
    EXPECT_EQ(bst.maximum(), 70);
    EXPECT_TRUE(bst.exists(-30));
    EXPECT_TRUE(bst.exists(0));
}

// Test large tree
TEST_F(BSTTest, LargeTree) {
    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(bst.insert(i * 2));
    }

    EXPECT_EQ(bst.minimum(), 0);
    EXPECT_EQ(bst.maximum(), 198);
    EXPECT_TRUE(bst.exists(50));
    EXPECT_FALSE(bst.exists(51));
}
