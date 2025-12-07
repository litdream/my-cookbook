#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void print_tree_inorder(BSTNode *root) {
    if (root == NULL)
        return;
    print_tree_inorder(root->left);
    printf("%d ", root->data);
    print_tree_inorder(root->right);
}

void print_tree_structure(BSTNode *root, int level) {
    if (root == NULL)
        return;

    print_tree_structure(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%d\n", root->data);
    print_tree_structure(root->left, level + 1);
    
}

void test_insert_and_exists() {
    printf("\n=== Test 1: Insert and Exists ===\n");
    BSTNode *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = bst_insert(root, values[i]);
    }
    printf("\n");

    printf("\nTree structure:\n");
    print_tree_structure(root, 0);

    printf("\nIn-order traversal: ");
    print_tree_inorder(root);
    printf("\n");

    printf("\nChecking existence:\n");
    printf("  50 exists: %s\n", bst_exists(root, 50) ? "true" : "false");
    printf("  60 exists: %s\n", bst_exists(root, 60) ? "true" : "false");
    printf("  100 exists: %s\n", bst_exists(root, 100) ? "true" : "false");
    printf("  20 exists: %s\n", bst_exists(root, 20) ? "true" : "false");
}

void test_duplicate_insert() {
    printf("\n=== Test 2: Duplicate Insert ===\n");
    BSTNode *root = NULL;

    root = bst_insert(root, 50);
    printf("Inserted 50, root = %p\n", (void*)root);

    BSTNode *result = bst_insert(root, 50);
    printf("Tried to insert 50 again, result = %p (should be NULL)\n", (void*)result);
}

void test_min_max() {
    printf("\n=== Test 3: Minimum and Maximum ===\n");
    BSTNode *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = bst_insert(root, values[i]);
    }
    printf("\n");

    printf("\nTree structure:\n");
    print_tree_structure(root, 0);

    printf("\nMinimum value: %d\n", bst_minimum(root));
    printf("Maximum value: %d\n", bst_maximum(root));
}

void test_height() {
    printf("\n=== Test 4: Tree Height ===\n");
    BSTNode *root = NULL;

    printf("Empty tree height: %d\n", bst_height(root));

    root = bst_insert(root, 50);
    printf("Single node height: %d\n", bst_height(root));

    root = bst_insert(root, 30);
    root = bst_insert(root, 70);
    printf("Three nodes (balanced) height: %d\n", bst_height(root));

    root = bst_insert(root, 20);
    root = bst_insert(root, 10);
    printf("After adding left chain height: %d\n", bst_height(root));

    printf("\nFinal tree structure:\n");
    print_tree_structure(root, 0);
}

void test_edge_cases() {
    printf("\n=== Test 5: Edge Cases ===\n");
    BSTNode *root = NULL;

    printf("Testing single node tree:\n");
    root = bst_insert(root, 42);
    printf("  Inserted 42\n");
    printf("  42 exists: %s\n", bst_exists(root, 42) ? "true" : "false");
    printf("  99 exists: %s\n", bst_exists(root, 99) ? "true" : "false");
    printf("  Minimum: %d\n", bst_minimum(root));
    printf("  Maximum: %d\n", bst_maximum(root));
    printf("  Height: %d\n", bst_height(root));

    printf("\nTesting left-skewed tree:\n");
    root = NULL;
    for (int i = 100; i > 0; i -= 10) {
        root = bst_insert(root, i);
    }
    printf("  In-order: ");
    print_tree_inorder(root);
    printf("\n");
    printf("  Height: %d\n", bst_height(root));
    printf("  Min: %d, Max: %d\n", bst_minimum(root), bst_maximum(root));
}

void test_delete() {
    printf("\n=== Test 6: Delete Operations ===\n");
    BSTNode *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Building tree with values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = bst_insert(root, values[i]);
    }
    printf("\n");

    printf("\nInitial tree structure:\n");
    print_tree_structure(root, 0);

    printf("\nIn-order traversal: ");
    print_tree_inorder(root);
    printf("\n");

    // Test 1: Delete leaf node
    printf("\n--- Deleting leaf node 10 ---\n");
    root = bst_delete(root, 10);
    printf("Tree after deletion:\n");
    print_tree_structure(root, 0);
    printf("In-order: ");
    print_tree_inorder(root);
    printf("\n10 exists: %s\n", bst_exists(root, 10) ? "true" : "false");

    // Test 2: Delete node with one child
    printf("\n--- Deleting node 20 (has one child: 25) ---\n");
    root = bst_delete(root, 20);
    printf("Tree after deletion:\n");
    print_tree_structure(root, 0);
    printf("In-order: ");
    print_tree_inorder(root);
    printf("\n20 exists: %s\n", bst_exists(root, 20) ? "true" : "false");

    // Test 3: Delete node with two children
    printf("\n--- Deleting node 30 (has two children) ---\n");
    root = bst_delete(root, 30);
    printf("Tree after deletion:\n");
    print_tree_structure(root, 0);
    printf("In-order: ");
    print_tree_inorder(root);
    printf("\n30 exists: %s\n", bst_exists(root, 30) ? "true" : "false");

    // Test 4: Delete root node
    printf("\n--- Deleting root node 50 ---\n");
    root = bst_delete(root, 50);
    printf("Tree after deletion:\n");
    print_tree_structure(root, 0);
    printf("In-order: ");
    print_tree_inorder(root);
    printf("\n50 exists: %s\n", bst_exists(root, 50) ? "true" : "false");

    // Test 5: Delete non-existent node
    printf("\n--- Trying to delete non-existent node 999 ---\n");
    root = bst_delete(root, 999);
    printf("Tree unchanged:\n");
    print_tree_structure(root, 0);
}

int main() {
    printf("BST Library Test Suite\n");
    printf("======================\n");

    test_insert_and_exists();
    test_duplicate_insert();
    test_min_max();
    test_height();
    test_edge_cases();
    test_delete();

    printf("\n======================\n");
    printf("All tests completed!\n");

    return 0;
}
