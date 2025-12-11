#include "maxheap.hpp"
#include <optional>
#include <algorithm>

std::optional<int>
MaxHeap::peek() const {
    if (isEmpty())
        return std::nullopt;
    return heap[0];
}

std::optional<int>
MaxHeap::extract()  {
    if (isEmpty())
        return std::nullopt;

    int max_val = heap[0];
    if (heap.size() == 1) {
        heap.pop_back();
    } else {
        // heap-vector size is more than 2.
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    return max_val;
}

void 
MaxHeap::insert(int item) {
	heap.push_back(item);
	heapifyUp(heap.size() -1);
}

void
MaxHeap::heapifyUp(size_t child_idx) {
    while (child_idx > 0) {
        size_t  par_idx = getParentIndex(child_idx);
        if ( heap[child_idx] > heap[par_idx] ) {
            std::swap(heap[child_idx], heap[par_idx]);
            child_idx = par_idx;
        } else {
            break;
        }
    }
}

void
MaxHeap::heapifyDown(size_t par_idx) {
    size_t  last_idx = heap.size() -1;
    while(true) {
        size_t largest_idx = par_idx;
        size_t left_child_idx = getLeftChildIndex(par_idx);
        size_t right_child_idx = getRightChildIndex(par_idx);

        // pick the largest of 3.
        if ( left_child_idx <= last_idx && heap[left_child_idx] > heap[largest_idx])
            largest_idx = left_child_idx;
        if ( right_child_idx <= last_idx && heap[right_child_idx] > heap[largest_idx])
            largest_idx = right_child_idx;

        if (largest_idx == par_idx)
            break;    // This meets Heap property.  Stop traversing.

        std::swap(heap[par_idx], heap[largest_idx]);
        par_idx = largest_idx;
    }
}
