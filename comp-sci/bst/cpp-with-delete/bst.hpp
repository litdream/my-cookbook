#ifndef RAY_BST_HPP
#define RAY_BST_HPP

#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST() = default;

    bool insert(int data);
    bool exists(int data) const;
    bool remove(int data);

    // We could use std::optional<int> here.
    int minimum() const;
    int maximum() const;
    int height() const;
    void printTree() const;

private:
    std::unique_ptr<Node> root;

    int _height(Node *subtree_root) const;
    void _printTree(Node *node, int level) const;
};

#endif // RAY_BST_HPP
