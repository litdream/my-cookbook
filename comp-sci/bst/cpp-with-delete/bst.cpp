#include "bst.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstdio>    // for perror
#include <cerrno>    // for global errno
#include <iostream>

BST::BST() : root(nullptr) {
}


// returns:
//   - true: successfully added.
//   - false: failed.  error occured.  (duplicate key)
//
bool
BST::insert(int data) {
    if (root == nullptr) {
        root = std::make_unique<Node>(data);
        return true;
    }

    Node *cur = root.get();
    Node *par = nullptr;

    while (cur != nullptr) {
        par = cur;
        if (data < cur->data) {
            cur = cur->left.get();
        } else if (data > cur->data ) {
            cur = cur->right.get();
        } else {
            // DUPLICATE!
            return false;
        }
    }

    if (data < par->data) {
        par->left = std::make_unique<Node>(data);
    } else {
        par->right = std::make_unique<Node>(data);
    }
    return true;
}

bool
BST::exists(int data) const {
    if (root == nullptr)
        return false;

    Node *cur = root.get();
    while ( cur != nullptr ) {
        if (data < cur->data) {
            cur = cur->left.get();
        } else if ( data > cur->data) {
            cur = cur->right.get();
        } else {
            return true;
        }
    }
    return false;
}

// returns:
//   - true: successfully deleted.
//   - false: failed. node not found.
//
bool
BST::remove(int data) {
    if (root == nullptr)
        return false;

    // Find the node to delete and its parent
    //   - Doing this will simplify tracing parent.
    //   - ownership switch (ptr->reset() ) will handle memory dealloc and parent pair.
    //
    // Summary:
    //    - *node_ptr : will adjust ownership.
    //    - *node     : will deference the pointer.
    //
    std::unique_ptr<Node> *node_ptr = &root;

    while (*node_ptr != nullptr) {
        Node *node = node_ptr->get();

        if (data < node->data) {
            node_ptr = &(node->left);
        } else if (data > node->data) {
            node_ptr = &(node->right);
        } else {
            // Found the node to delete

            // Case 1: Node has no children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                node_ptr->reset();
                return true;
            }

            // Case 2: Node has only right child
            if (node->left == nullptr) {
                *node_ptr = std::move(node->right);
                return true;
            }

            // Case 3: Node has only left child
            if (node->right == nullptr) {
                *node_ptr = std::move(node->left);
                return true;
            }

            // Case 4: Node has two children
            // Find the inorder successor (minimum in right subtree)
            Node *successor_parent = node;
            Node *successor = node->right.get();
            while (successor->left != nullptr) {
                successor_parent = successor;
                successor = successor->left.get();
            }

            // Copy successor's data to current node
            node->data = successor->data;

            // Delete the successor (which has at most one child - right child)
            if (successor_parent == node) {
                // Special case:  Successor is the right child of node
                //
                //    node
                //       \
                //       successor
                //         \
                //          TREE
                //
                node->right = std::move(successor->right);
            } else {
                // Successor is in the left subtree of node's right child
                //successor_parent->left = std::move(successor->left);    // intentional fail, for unittest
                successor_parent->left = std::move(successor->right);
            }

            return true;
        }
    }

    // Node not found
    return false;
}

// PRE: I don't handle empty-tree's minimum.
//   - it will crash.
int
BST::minimum() const {
    if (root == nullptr) {
        perror("ERROR: min() for empty tree.");
        exit(1);
    }
    Node *cur = root.get();
    while (cur->left != nullptr)
        cur = cur->left.get();
    return cur->data;
}
// PRE: I don't handle empty-tree's maximum.
//   - it will crash.
int
BST::maximum() const {
    if (root == nullptr) {
        perror("ERROR: min() for empty tree.");
        exit(1);
    }
    Node *cur = root.get();
    while (cur->right != nullptr)
        cur = cur->right.get();
    return cur->data;
}

int
BST::height() const {
    return _height(root.get());
}

int
BST::_height(Node *subtree_root) const {
    Node *node = subtree_root;
    if (node == nullptr)
        return -1;

    int left_height = _height(node->left.get());
    int right_height  = _height(node->right.get());
    return 1 + std::max(left_height, right_height);
}

void
BST::printTree() const {
    _printTree(root.get(), 0);
}

void
BST::_printTree(Node* node, int level) const {
    if (node == nullptr) {
        return;
    }

    _printTree(node->right.get(), level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << node->data << std::endl;
    _printTree(node->left.get(), level + 1);
}
