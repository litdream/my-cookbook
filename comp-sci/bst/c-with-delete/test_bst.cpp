#include <gtest/gtest.h>

extern "C" {
#include "bst.h"
}

class BSTTest : public ::testing::Test {
protected:
    BSTNode* root;

    void SetUp() override {
        root = nullptr;
    }

    void TearDown() override {
        // Clean up tree by deleting all nodes
        if (root != nullptr) {
            delete_tree(root);
            root = nullptr;
        }
    }

    // Helper to delete entire tree
    void delete_tree(BSTNode* node) {
        if (node == nullptr) return;
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }

    // Helper to build a standard test tree
    void build_standard_tree() {
        int values[] = {50, 30, 70, 20, 40, 60, 80};
        for (int val : values) {
            root = bst_insert(root, val);
        }
    }
};

// ============================================================================
// INSERT TESTS
// ============================================================================

TEST_F(BSTTest, InsertIntoEmptyTree) {
    root = bst_insert(root, 50);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 50);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
}

TEST_F(BSTTest, InsertMultipleValues) {
    build_standard_tree();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 50);
}

TEST_F(BSTTest, InsertDuplicateReturnsNull) {
    root = bst_insert(root, 50);
    BSTNode* result = bst_insert(root, 50);
    EXPECT_EQ(result, nullptr);
}

TEST_F(BSTTest, InsertMaintainsBSTProperty) {
    build_standard_tree();
    EXPECT_LT(root->left->data, root->data);
    EXPECT_GT(root->right->data, root->data);
    EXPECT_LT(root->left->left->data, root->left->data);
    EXPECT_GT(root->left->right->data, root->left->data);
}

// ============================================================================
// EXISTS TESTS
// ============================================================================

TEST_F(BSTTest, ExistsInEmptyTree) {
    EXPECT_FALSE(bst_exists(root, 50));
}

TEST_F(BSTTest, ExistsFindsRoot) {
    root = bst_insert(root, 50);
    EXPECT_TRUE(bst_exists(root, 50));
}

TEST_F(BSTTest, ExistsFindsAllValues) {
    build_standard_tree();
    EXPECT_TRUE(bst_exists(root, 50));
    EXPECT_TRUE(bst_exists(root, 30));
    EXPECT_TRUE(bst_exists(root, 70));
    EXPECT_TRUE(bst_exists(root, 20));
    EXPECT_TRUE(bst_exists(root, 40));
    EXPECT_TRUE(bst_exists(root, 60));
    EXPECT_TRUE(bst_exists(root, 80));
}

TEST_F(BSTTest, ExistsReturnsFalseForMissingValue) {
    build_standard_tree();
    EXPECT_FALSE(bst_exists(root, 100));
    EXPECT_FALSE(bst_exists(root, 25));
    EXPECT_FALSE(bst_exists(root, 1));
}

// ============================================================================
// MINIMUM / MAXIMUM TESTS
// ============================================================================

TEST_F(BSTTest, MinimumInSingleNode) {
    root = bst_insert(root, 50);
    EXPECT_EQ(bst_minimum(root), 50);
}

TEST_F(BSTTest, MaximumInSingleNode) {
    root = bst_insert(root, 50);
    EXPECT_EQ(bst_maximum(root), 50);
}

TEST_F(BSTTest, MinimumInBalancedTree) {
    build_standard_tree();
    EXPECT_EQ(bst_minimum(root), 20);
}

TEST_F(BSTTest, MaximumInBalancedTree) {
    build_standard_tree();
    EXPECT_EQ(bst_maximum(root), 80);
}

TEST_F(BSTTest, MinimumInLeftSkewedTree) {
    root = bst_insert(root, 100);
    root = bst_insert(root, 80);
    root = bst_insert(root, 60);
    root = bst_insert(root, 40);
    EXPECT_EQ(bst_minimum(root), 40);
}

TEST_F(BSTTest, MaximumInRightSkewedTree) {
    root = bst_insert(root, 10);
    root = bst_insert(root, 20);
    root = bst_insert(root, 30);
    root = bst_insert(root, 40);
    EXPECT_EQ(bst_maximum(root), 40);
}

// ============================================================================
// HEIGHT TESTS
// ============================================================================

TEST_F(BSTTest, HeightOfEmptyTree) {
    EXPECT_EQ(bst_height(root), -1);
}

TEST_F(BSTTest, HeightOfSingleNode) {
    root = bst_insert(root, 50);
    EXPECT_EQ(bst_height(root), 0);
}

TEST_F(BSTTest, HeightOfBalancedTree) {
    build_standard_tree();
    EXPECT_EQ(bst_height(root), 2);
}

TEST_F(BSTTest, HeightOfLeftSkewedTree) {
    root = bst_insert(root, 50);
    root = bst_insert(root, 40);
    root = bst_insert(root, 30);
    root = bst_insert(root, 20);
    EXPECT_EQ(bst_height(root), 3);
}

TEST_F(BSTTest, HeightOfRightSkewedTree) {
    root = bst_insert(root, 10);
    root = bst_insert(root, 20);
    root = bst_insert(root, 30);
    root = bst_insert(root, 40);
    EXPECT_EQ(bst_height(root), 3);
}

// ============================================================================
// DELETE TESTS
// ============================================================================

TEST_F(BSTTest, DeleteFromEmptyTree) {
    root = bst_delete(root, 50);
    EXPECT_EQ(root, nullptr);
}

TEST_F(BSTTest, DeleteNonExistentValue) {
    build_standard_tree();
    root = bst_delete(root, 999);
    EXPECT_TRUE(bst_exists(root, 50));
    EXPECT_EQ(bst_height(root), 2);
}

TEST_F(BSTTest, DeleteLeafNode) {
    build_standard_tree();
    root = bst_delete(root, 20);
    EXPECT_FALSE(bst_exists(root, 20));
    EXPECT_TRUE(bst_exists(root, 30));
    EXPECT_EQ(root->left->left, nullptr);
}

TEST_F(BSTTest, DeleteNodeWithOnlyLeftChild) {
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 20);

    root = bst_delete(root, 30);
    EXPECT_FALSE(bst_exists(root, 30));
    EXPECT_TRUE(bst_exists(root, 20));
    EXPECT_EQ(root->left->data, 20);
}

TEST_F(BSTTest, DeleteNodeWithOnlyRightChild) {
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 40);

    root = bst_delete(root, 30);
    EXPECT_FALSE(bst_exists(root, 30));
    EXPECT_TRUE(bst_exists(root, 40));
    EXPECT_EQ(root->left->data, 40);
}

TEST_F(BSTTest, DeleteNodeWithTwoChildren) {
    build_standard_tree();
    root = bst_delete(root, 30);

    EXPECT_FALSE(bst_exists(root, 30));
    EXPECT_TRUE(bst_exists(root, 20));
    EXPECT_TRUE(bst_exists(root, 40));

    // After deleting 30, the in-order successor (40) should replace it
    EXPECT_EQ(root->left->data, 40);
}

TEST_F(BSTTest, DeleteRootNodeWithNoChildren) {
    root = bst_insert(root, 50);
    root = bst_delete(root, 50);
    EXPECT_EQ(root, nullptr);
}

TEST_F(BSTTest, DeleteRootNodeWithOneChild) {
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_delete(root, 50);

    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->data, 30);
}

TEST_F(BSTTest, DeleteRootNodeWithTwoChildren) {
    build_standard_tree();
    root = bst_delete(root, 50);

    EXPECT_FALSE(bst_exists(root, 50));
    EXPECT_TRUE(bst_exists(root, 30));
    EXPECT_TRUE(bst_exists(root, 70));

    // After deleting root 50, successor (60) should become new root
    EXPECT_EQ(root->data, 60);
}

TEST_F(BSTTest, DeleteAllNodesOneByOne) {
    build_standard_tree();

    int values[] = {20, 40, 30, 60, 80, 70, 50};
    for (int val : values) {
        root = bst_delete(root, val);
        EXPECT_FALSE(bst_exists(root, val));
    }

    EXPECT_EQ(root, nullptr);
}

TEST_F(BSTTest, DeleteAndReinsert) {
    build_standard_tree();

    root = bst_delete(root, 30);
    EXPECT_FALSE(bst_exists(root, 30));

    root = bst_insert(root, 30);
    EXPECT_TRUE(bst_exists(root, 30));
}

// ============================================================================
// COMPLEX SCENARIO TESTS
// ============================================================================

TEST_F(BSTTest, ComplexDeleteSequence) {
    // Build larger tree
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int val : values) {
        root = bst_insert(root, val);
    }

    // Delete in various orders
    root = bst_delete(root, 10);  // Leaf
    root = bst_delete(root, 20);  // One child
    root = bst_delete(root, 30);  // Two children

    EXPECT_FALSE(bst_exists(root, 10));
    EXPECT_FALSE(bst_exists(root, 20));
    EXPECT_FALSE(bst_exists(root, 30));

    // Check remaining values still exist
    EXPECT_TRUE(bst_exists(root, 25));
    EXPECT_TRUE(bst_exists(root, 35));
    EXPECT_TRUE(bst_exists(root, 40));
    EXPECT_TRUE(bst_exists(root, 45));
}

TEST_F(BSTTest, StressTestInsertDeleteCycle) {
    // Insert values
    for (int i = 1; i <= 20; i++) {
        root = bst_insert(root, i * 5);
    }

    // Delete even multiples
    for (int i = 2; i <= 20; i += 2) {
        root = bst_delete(root, i * 5);
    }

    // Verify odd multiples still exist
    for (int i = 1; i <= 20; i += 2) {
        EXPECT_TRUE(bst_exists(root, i * 5));
    }

    // Verify even multiples are gone
    for (int i = 2; i <= 20; i += 2) {
        EXPECT_FALSE(bst_exists(root, i * 5));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
