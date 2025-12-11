#include "gtest/gtest.h"
#include "maxheap.hpp"

TEST(MaxHeapTest, IsEmptyInitially) {
    MaxHeap heap;
    ASSERT_TRUE(heap.isEmpty());
    ASSERT_EQ(heap.size(), 0);
}

TEST(MaxHeapTest, InsertSingleElement) {
    MaxHeap heap;
    heap.insert(10);
    ASSERT_FALSE(heap.isEmpty());
    ASSERT_EQ(heap.size(), 1);
    ASSERT_EQ(heap.peek().value_or(-1), 10);
}

TEST(MaxHeapTest, InsertMultipleElementsAndPeek) {
    MaxHeap heap;
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    ASSERT_EQ(heap.size(), 3);
    ASSERT_EQ(heap.peek().value_or(-1), 20);
}

TEST(MaxHeapTest, ExtractMaxFromSingleElement) {
    MaxHeap heap;
    heap.insert(100);
    ASSERT_EQ(heap.extract().value_or(-1), 100);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, ExtractMaxFromMultipleElements) {
    MaxHeap heap;
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(15);
    heap.insert(25);

    ASSERT_EQ(heap.extract().value_or(-1), 25);
    ASSERT_EQ(heap.size(), 4);
    ASSERT_EQ(heap.extract().value_or(-1), 20);
    ASSERT_EQ(heap.size(), 3);
    ASSERT_EQ(heap.extract().value_or(-1), 15);
    ASSERT_EQ(heap.size(), 2);
    ASSERT_EQ(heap.extract().value_or(-1), 10);
    ASSERT_EQ(heap.size(), 1);
    ASSERT_EQ(heap.extract().value_or(-1), 5);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, PeekOnEmptyHeap) {
    MaxHeap heap;
    ASSERT_FALSE(heap.peek().has_value());
}

TEST(MaxHeapTest, ExtractOnEmptyHeap) {
    MaxHeap heap;
    ASSERT_FALSE(heap.extract().has_value());
}
