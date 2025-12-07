#include "bst.hpp"
#include <iostream>

void print_tree_inorder(const BST& bst, Node* node) {
    // Note: This is a helper that would need friend access
    // For standalone test, we'll skip inorder printing
    // or would need to modify BST to expose inorder traversal
}

void test_insert_and_exists() {
    std::cout << "\n=== Test 1: Insert and Exists ===" << std::endl;
    BST bst;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    std::cout << "Inserting values: ";
    for (int i = 0; i < n; i++) {
        std::cout << values[i] << " ";
        bst.insert(values[i]);
    }
    std::cout << std::endl;

    std::cout << "\nTree structure:" << std::endl;
    bst.printTree();

    std::cout << "\nChecking existence:" << std::endl;
    std::cout << "  50 exists: " << (bst.exists(50) ? "true" : "false") << std::endl;
    std::cout << "  60 exists: " << (bst.exists(60) ? "true" : "false") << std::endl;
    std::cout << "  100 exists: " << (bst.exists(100) ? "true" : "false") << std::endl;
    std::cout << "  20 exists: " << (bst.exists(20) ? "true" : "false") << std::endl;
}

void test_duplicate_insert() {
    std::cout << "\n=== Test 2: Duplicate Insert ===" << std::endl;
    BST bst;

    bool result1 = bst.insert(50);
    std::cout << "Inserted 50, result = " << (result1 ? "true" : "false") << std::endl;

    bool result2 = bst.insert(50);
    std::cout << "Tried to insert 50 again, result = " << (result2 ? "true" : "false")
              << " (should be false)" << std::endl;
}

void test_min_max() {
    std::cout << "\n=== Test 3: Minimum and Maximum ===" << std::endl;
    BST bst;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);

    std::cout << "Inserting values: ";
    for (int i = 0; i < n; i++) {
        std::cout << values[i] << " ";
        bst.insert(values[i]);
    }
    std::cout << std::endl;

    std::cout << "\nTree structure:" << std::endl;
    bst.printTree();

    std::cout << "\nMinimum value: " << bst.minimum() << std::endl;
    std::cout << "Maximum value: " << bst.maximum() << std::endl;
}

void test_height() {
    std::cout << "\n=== Test 4: Tree Height ===" << std::endl;
    BST bst;

    std::cout << "Empty tree height: " << bst.height() << std::endl;

    bst.insert(50);
    std::cout << "Single node height: " << bst.height() << std::endl;

    bst.insert(30);
    bst.insert(70);
    std::cout << "Three nodes (balanced) height: " << bst.height() << std::endl;

    bst.insert(20);
    bst.insert(10);
    std::cout << "After adding left chain height: " << bst.height() << std::endl;

    std::cout << "\nFinal tree structure:" << std::endl;
    bst.printTree();
}

void test_edge_cases() {
    std::cout << "\n=== Test 5: Edge Cases ===" << std::endl;
    BST bst;

    std::cout << "Testing single node tree:" << std::endl;
    bst.insert(42);
    std::cout << "  Inserted 42" << std::endl;
    std::cout << "  42 exists: " << (bst.exists(42) ? "true" : "false") << std::endl;
    std::cout << "  99 exists: " << (bst.exists(99) ? "true" : "false") << std::endl;
    std::cout << "  Minimum: " << bst.minimum() << std::endl;
    std::cout << "  Maximum: " << bst.maximum() << std::endl;
    std::cout << "  Height: " << bst.height() << std::endl;

    std::cout << "\nTesting left-skewed tree:" << std::endl;
    BST bst2;
    for (int i = 100; i > 0; i -= 10) {
        bst2.insert(i);
    }
    std::cout << "  Height: " << bst2.height() << std::endl;
    std::cout << "  Min: " << bst2.minimum() << ", Max: " << bst2.maximum() << std::endl;
}

int main() {
    std::cout << "BST Library Test Suite" << std::endl;
    std::cout << "======================" << std::endl;

    test_insert_and_exists();
    test_duplicate_insert();
    test_min_max();
    test_height();
    test_edge_cases();

    std::cout << "\n======================" << std::endl;
    std::cout << "All tests completed!" << std::endl;

    return 0;
}
