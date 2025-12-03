#ifndef CPP_LLIST_HPP
#define CPP_LLIST_HPP

#include <iostream>
#include <memory>

class LList {
public:
    LList();

    void push(int data);
    int pop(); // Returns the popped value
    void remove(int data);
    bool search(int data) const;
    int min() const;
    int max() const;
    void print() const;
    int size() const;
    bool isEmpty() const;
    void add(int data);
    int getAt(int index) const;

private:
    struct Node {
        int data;
        std::unique_ptr<Node> next;
        Node(int d) : data(d), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    int list_size;
};

#endif // CPP_LLIST_HPP
