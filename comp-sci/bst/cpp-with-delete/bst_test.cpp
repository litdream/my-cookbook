#include "bst.hpp"
#include <gtest/gtest.h>

class BSTTest : public ::testing::Test {
protected:
    BST bst;
};

// Insert tests
TEST_F(BSTTest, InsertSingleElement) {
    EXPECT_TRUE(bst.insert(50));
    EXPECT_TRUE(bst.exists(50));
}

TEST_F(BSTTest, InsertMultipleElements) {
    EXPECT_TRUE(bst.insert(50));
    EXPECT_TRUE(bst.insert(30));
    EXPECT_TRUE(bst.insert(70));

    EXPECT_TRUE(bst.exists(50));
    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(70));
}

TEST_F(BSTTest, InsertDuplicateReturnsFalse) {
    EXPECT_TRUE(bst.insert(50));
    EXPECT_FALSE(bst.insert(50));
}

// Exists tests
TEST_F(BSTTest, ExistsReturnsFalseForEmptyTree) {
    EXPECT_FALSE(bst.exists(50));
}

TEST_F(BSTTest, ExistsReturnsFalseForNonExistentElement) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);

    EXPECT_FALSE(bst.exists(100));
    EXPECT_FALSE(bst.exists(25));
}

// Minimum and Maximum tests
TEST_F(BSTTest, MinimumInSingleNodeTree) {
    bst.insert(50);
    EXPECT_EQ(bst.minimum(), 50);
}

TEST_F(BSTTest, MaximumInSingleNodeTree) {
    bst.insert(50);
    EXPECT_EQ(bst.maximum(), 50);
}

TEST_F(BSTTest, MinimumAndMaximumInMultiNodeTree) {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10};
    for (int val : values) {
        bst.insert(val);
    }

    EXPECT_EQ(bst.minimum(), 10);
    EXPECT_EQ(bst.maximum(), 80);
}

// Height tests
TEST_F(BSTTest, HeightOfEmptyTree) {
    EXPECT_EQ(bst.height(), -1);
}

TEST_F(BSTTest, HeightOfSingleNode) {
    bst.insert(50);
    EXPECT_EQ(bst.height(), 0);
}

TEST_F(BSTTest, HeightOfBalancedTree) {
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

TEST_F(BSTTest, HeightOfSkewedTree) {
    for (int i = 1; i <= 5; i++) {
        bst.insert(i);
    }
    EXPECT_EQ(bst.height(), 4);
}

// Remove tests - leaf node
TEST_F(BSTTest, RemoveLeafNode) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);

    EXPECT_TRUE(bst.remove(20));
    EXPECT_FALSE(bst.exists(20));
    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(50));
}

// Remove tests - node with one child
TEST_F(BSTTest, RemoveNodeWithOnlyLeftChild) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(60);

    EXPECT_TRUE(bst.remove(70));
    EXPECT_FALSE(bst.exists(70));
    EXPECT_TRUE(bst.exists(60));
    EXPECT_TRUE(bst.exists(50));
}

TEST_F(BSTTest, RemoveNodeWithOnlyRightChild) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(80);

    EXPECT_TRUE(bst.remove(70));
    EXPECT_FALSE(bst.exists(70));
    EXPECT_TRUE(bst.exists(80));
    EXPECT_TRUE(bst.exists(50));
}

// Remove tests - node with two children
TEST_F(BSTTest, RemoveNodeWithTwoChildren) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    EXPECT_TRUE(bst.remove(30));
    EXPECT_FALSE(bst.exists(30));
    EXPECT_TRUE(bst.exists(20));
    EXPECT_TRUE(bst.exists(40));
    EXPECT_TRUE(bst.exists(50));
}

// Remove tests - root node
TEST_F(BSTTest, RemoveRootNodeWithNoChildren) {
    bst.insert(50);

    EXPECT_TRUE(bst.remove(50));
    EXPECT_FALSE(bst.exists(50));
    EXPECT_EQ(bst.height(), -1);
}

TEST_F(BSTTest, RemoveRootNodeWithOneChild) {
    bst.insert(50);
    bst.insert(30);

    EXPECT_TRUE(bst.remove(50));
    EXPECT_FALSE(bst.exists(50));
    EXPECT_TRUE(bst.exists(30));
    EXPECT_EQ(bst.minimum(), 30);
}

TEST_F(BSTTest, RemoveRootNodeWithTwoChildren) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    EXPECT_TRUE(bst.remove(50));
    EXPECT_FALSE(bst.exists(50));
    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(70));
    EXPECT_EQ(bst.minimum(), 20);
    EXPECT_EQ(bst.maximum(), 80);
}

// Remove tests - non-existent node
TEST_F(BSTTest, RemoveNonExistentNode) {
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);

    EXPECT_FALSE(bst.remove(100));
    EXPECT_TRUE(bst.exists(50));
    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(70));
}

TEST_F(BSTTest, RemoveFromEmptyTree) {
    EXPECT_FALSE(bst.remove(50));
}

// Remove tests - multiple deletions
TEST_F(BSTTest, RemoveMultipleNodes) {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int val : values) {
        bst.insert(val);
    }

    EXPECT_TRUE(bst.remove(25));
    EXPECT_TRUE(bst.remove(60));
    EXPECT_TRUE(bst.remove(30));
    EXPECT_TRUE(bst.remove(50));

    EXPECT_FALSE(bst.exists(25));
    EXPECT_FALSE(bst.exists(60));
    EXPECT_FALSE(bst.exists(30));
    EXPECT_FALSE(bst.exists(50));

    EXPECT_TRUE(bst.exists(20));
    EXPECT_TRUE(bst.exists(70));
    EXPECT_TRUE(bst.exists(10));
}

// Remove tests - verify tree properties after deletion
TEST_F(BSTTest, TreePropertiesAfterDeletion) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values) {
        bst.insert(val);
    }

    bst.remove(30);

    EXPECT_EQ(bst.minimum(), 20);
    EXPECT_EQ(bst.maximum(), 80);
    EXPECT_GE(bst.height(), 2);
}

// Remove all nodes one by one
TEST_F(BSTTest, RemoveAllNodes) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values) {
        bst.insert(val);
    }

    for (int val : values) {
        EXPECT_TRUE(bst.remove(val));
    }

    EXPECT_EQ(bst.height(), -1);
    for (int val : values) {
        EXPECT_FALSE(bst.exists(val));
    }
}

// Complex scenario test
TEST_F(BSTTest, ComplexInsertRemoveSequence) {
    bst.insert(50);
    bst.insert(25);
    bst.insert(75);
    bst.insert(10);
    bst.insert(30);

    EXPECT_TRUE(bst.remove(25));
    EXPECT_FALSE(bst.exists(25));

    bst.insert(35);
    bst.insert(28);

    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(35));
    EXPECT_TRUE(bst.exists(28));

    EXPECT_TRUE(bst.remove(30));

    EXPECT_TRUE(bst.exists(35));
    EXPECT_TRUE(bst.exists(28));
}

// Test case for successor with right child (line 123 bug)
TEST_F(BSTTest, RemoveNodeWhenSuccessorHasRightChild) {
    // Build tree where successor of node to delete has a right child
    //       50
    //      /  \
    //    30    70
    //   / \   /  \
    //  20 40 60  80
    //           /
    //          65
    //            \
    //            67
    //
    // When we delete 50, successor is 60
    // Successor 60 has right child 65
    // Line 123 must move successor's RIGHT child, not left child

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    bst.insert(65);
    bst.insert(67);

    // Delete 50 - successor will be 60 which has right child 65
    EXPECT_TRUE(bst.remove(50));
    EXPECT_FALSE(bst.exists(50));

    // Verify successor (60) replaced 50
    EXPECT_TRUE(bst.exists(60));

    // Verify successor's right child (65) and its child (67) still exist
    EXPECT_TRUE(bst.exists(65));
    EXPECT_TRUE(bst.exists(67));

    // Verify all other nodes still exist
    EXPECT_TRUE(bst.exists(30));
    EXPECT_TRUE(bst.exists(70));
    EXPECT_TRUE(bst.exists(20));
    EXPECT_TRUE(bst.exists(40));
    EXPECT_TRUE(bst.exists(80));

    // Verify tree properties
    EXPECT_EQ(bst.minimum(), 20);
    EXPECT_EQ(bst.maximum(), 80);
}
