#ifndef RAY_MAXHEAP_HPP
#define RAY_MAXHEAP_HPP

#include <vector>
#include <optional>
class MaxHeap {
public:
    void insert(int item);
    size_t size() const {
        return heap.size();
    }
    bool isEmpty() const {
        return heap.empty();
    }

    std::optional<int> peek() const;
    std::optional<int> extract();

private:
    std::vector<int> heap;

    size_t  getParentIndex(size_t  child_idx) const {
        return (child_idx - 1) /2;
    }
    size_t  getLeftChildIndex(size_t  par_idx) const {
        return  2 * par_idx + 1;
    }
    size_t  getRightChildIndex(size_t  par_idx) const {
        return  2 * par_idx + 2;
    }

    void heapifyUp(size_t child_idx);
    void heapifyDown(size_t par_idx);
};

#endif  // RAY_MAXHEAP_HPP
