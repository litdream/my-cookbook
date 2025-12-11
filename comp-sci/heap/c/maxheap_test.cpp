#include "gtest/gtest.h"
#include "maxheap.h"
#include <vector> // Required for std::vector
#include <algorithm> // Required for std::sort
#include <random> // Required for random number generation


// Helper function to check if the heap is a valid max-heap
void verify_max_heap(MaxHeap *heap) {
    for (size_t i = 0; i < heap->size; ++i) {
        size_t left_child = 2 * i + 1;
        size_t right_child = 2 * i + 2;

        if (left_child < heap->size) {
            ASSERT_GE(heap->data[i], heap->data[left_child]);
        }
        if (right_child < heap->size) {
            ASSERT_GE(heap->data[i], heap->data[right_child]);
        }
    }
}

TEST(MaxHeapTest, Initialization) {
    MaxHeap heap;
    maxheap_init(&heap);
    ASSERT_EQ(heap.size, 0);
}

TEST(MaxHeapTest, EmptyHeapPeekAndExtract) {
    MaxHeap heap;
    maxheap_init(&heap);
    ASSERT_EQ(maxheap_peek(&heap), INT_MIN);
    ASSERT_EQ(maxheap_extract(&heap), INT_MIN);
    ASSERT_EQ(heap.size, 0);
}

TEST(MaxHeapTest, InsertSingleItem) {
    MaxHeap heap;
    maxheap_init(&heap);
    ASSERT_EQ(maxheap_insert(&heap, 10), 0);
    ASSERT_EQ(heap.size, 1);
    ASSERT_EQ(maxheap_peek(&heap), 10);
    verify_max_heap(&heap);
}

TEST(MaxHeapTest, InsertMultipleItemsAndPeek) {
    MaxHeap heap;
    maxheap_init(&heap);
    maxheap_insert(&heap, 10);
    maxheap_insert(&heap, 20);
    maxheap_insert(&heap, 5);
    maxheap_insert(&heap, 25);

    ASSERT_EQ(heap.size, 4);
    ASSERT_EQ(maxheap_peek(&heap), 25);
    verify_max_heap(&heap);
}

TEST(MaxHeapTest, InsertAndExtractMultipleItems) {
    MaxHeap heap;
    maxheap_init(&heap);
    maxheap_insert(&heap, 10);
    maxheap_insert(&heap, 20);
    maxheap_insert(&heap, 5);
    maxheap_insert(&heap, 25);

    ASSERT_EQ(maxheap_extract(&heap), 25);
    ASSERT_EQ(heap.size, 3);
    ASSERT_EQ(maxheap_peek(&heap), 20);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), 20);
    ASSERT_EQ(heap.size, 2);
    ASSERT_EQ(maxheap_peek(&heap), 10);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), 10);
    ASSERT_EQ(heap.size, 1);
    ASSERT_EQ(maxheap_peek(&heap), 5);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), 5);
    ASSERT_EQ(heap.size, 0);
    ASSERT_EQ(maxheap_peek(&heap), INT_MIN);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), INT_MIN); // Extract from empty
}

TEST(MaxHeapTest, InsertDuplicateValues) {
    MaxHeap heap;
    maxheap_init(&heap);
    maxheap_insert(&heap, 10);
    maxheap_insert(&heap, 20);
    maxheap_insert(&heap, 10);
    maxheap_insert(&heap, 20);

    ASSERT_EQ(heap.size, 4);
    ASSERT_EQ(maxheap_peek(&heap), 20);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), 20);
    ASSERT_EQ(maxheap_extract(&heap), 20);
    ASSERT_EQ(maxheap_extract(&heap), 10);
    ASSERT_EQ(maxheap_extract(&heap), 10);
    ASSERT_EQ(heap.size, 0);
}

TEST(MaxHeapTest, InsertNegativeValues) {
    MaxHeap heap;
    maxheap_init(&heap);
    maxheap_insert(&heap, -10);
    maxheap_insert(&heap, -5);
    maxheap_insert(&heap, -20);
    maxheap_insert(&heap, 0);

    ASSERT_EQ(heap.size, 4);
    ASSERT_EQ(maxheap_peek(&heap), 0);
    verify_max_heap(&heap);

    ASSERT_EQ(maxheap_extract(&heap), 0);
    ASSERT_EQ(maxheap_extract(&heap), -5);
    ASSERT_EQ(maxheap_extract(&heap), -10);
    ASSERT_EQ(maxheap_extract(&heap), -20);
    ASSERT_EQ(heap.size, 0);
}

TEST(MaxHeapTest, HeapFull) {
    MaxHeap heap;
    maxheap_init(&heap);

    for (int i = 0; i < MAX_HEAP_SIZE; ++i) {
        ASSERT_EQ(maxheap_insert(&heap, i), 0);
    }
    ASSERT_EQ(heap.size, MAX_HEAP_SIZE);
    ASSERT_EQ(maxheap_insert(&heap, 999), -1); // Should fail
    ASSERT_EQ(heap.size, MAX_HEAP_SIZE); // Size should remain max
    verify_max_heap(&heap);

    // Verify extraction order
    for (int i = MAX_HEAP_SIZE - 1; i >= 0; --i) {
        ASSERT_EQ(maxheap_extract(&heap), i);
    }
    ASSERT_EQ(heap.size, 0);
}

TEST(MaxHeapTest, LargeNumberOfRandomInsertsAndExtracts) {
    MaxHeap heap;
    maxheap_init(&heap);
    std::vector<int> expected_sorted_values;

    // Insert random values
    srand(0); // For reproducibility
    for (int i = 0; i < MAX_HEAP_SIZE - 10; ++i) { // Leave some space
        int val = rand() % 1000;
        maxheap_insert(&heap, val);
        expected_sorted_values.push_back(val);
    }
    verify_max_heap(&heap);

    // Sort expected values in descending order
    std::sort(expected_sorted_values.rbegin(), expected_sorted_values.rend());

    // Extract and compare
    for (size_t i = 0; i < expected_sorted_values.size(); ++i) {
        ASSERT_EQ(maxheap_extract(&heap), expected_sorted_values[i]);
        verify_max_heap(&heap);
    }
    ASSERT_EQ(heap.size, 0);
}
