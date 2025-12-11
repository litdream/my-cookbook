#include "gtest/gtest.h"
#include "maxheap.hpp"
#include <climits>

TEST(MaxHeapTest, IsEmptyInitially) {
    MaxHeap heap;
    ASSERT_TRUE(heap.isEmpty());
    ASSERT_EQ(heap.size(), 0);
}

TEST(MaxHeapTest, IsEmptyInitiallyInvalidPeek) {
    MaxHeap heap;
    ASSERT_TRUE(heap.isEmpty());
    ASSERT_EQ(heap.size(), 0);
    ASSERT_EQ(heap.peek(), std::nullopt);
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

TEST(MaxHeapTest, InsertAndExtractINT_MIN) {
    MaxHeap heap;
    heap.insert(INT_MIN);
    ASSERT_FALSE(heap.isEmpty());
    ASSERT_EQ(heap.size(), 1);
    ASSERT_EQ(heap.peek().value_or(-1), INT_MIN);
    ASSERT_EQ(heap.extract().value_or(-1), INT_MIN);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, InsertNegativeNumbers) {
    MaxHeap heap;
    heap.insert(-10);
    heap.insert(-5);
    heap.insert(-20);
    ASSERT_EQ(heap.peek().value_or(0), -5);
    ASSERT_EQ(heap.extract().value_or(0), -5);
    ASSERT_EQ(heap.extract().value_or(0), -10);
    ASSERT_EQ(heap.extract().value_or(0), -20);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, InsertDuplicateNumbers) {
    MaxHeap heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(10);
    heap.insert(30);
    heap.insert(20);
    
    ASSERT_EQ(heap.size(), 5);
    ASSERT_EQ(heap.extract().value_or(0), 30);
    ASSERT_EQ(heap.extract().value_or(0), 20);
    ASSERT_EQ(heap.extract().value_or(0), 20);
    ASSERT_EQ(heap.extract().value_or(0), 10);
    ASSERT_EQ(heap.extract().value_or(0), 10);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, LargeNumberOfElements) {
    MaxHeap heap;
    for (int i = 0; i < 1000; ++i) {
        heap.insert(i);
    }
    ASSERT_EQ(heap.size(), 1000);
    for (int i = 999; i >= 0; --i) {
        ASSERT_EQ(heap.extract().value_or(-1), i);
    }
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, MixedNumbers) {
    MaxHeap heap;
    heap.insert(0);
    heap.insert(-10);
    heap.insert(20);
    heap.insert(-5);
    heap.insert(15);
    heap.insert(-20);
    heap.insert(10);

    ASSERT_EQ(heap.extract().value_or(-1), 20);
    ASSERT_EQ(heap.extract().value_or(-1), 15);
    ASSERT_EQ(heap.extract().value_or(-1), 10);
    ASSERT_EQ(heap.extract().value_or(-1), 0);
    ASSERT_EQ(heap.extract().value_or(-1), -5);
    ASSERT_EQ(heap.extract().value_or(-1), -10);
    ASSERT_EQ(heap.extract().value_or(-1), -20);
    ASSERT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, HeapPropertyAfterInsertsAndExtracts) {
    MaxHeap heap;
    heap.insert(50);
    heap.insert(30);
    heap.insert(40);
    ASSERT_EQ(heap.peek().value_or(-1), 50); // 50 is max
    heap.insert(60);
    ASSERT_EQ(heap.peek().value_or(-1), 60); // 60 is max
    heap.extract(); // extract 60
    ASSERT_EQ(heap.peek().value_or(-1), 50); // 50 is next max
    heap.insert(20);
    heap.insert(70);
    ASSERT_EQ(heap.peek().value_or(-1), 70); // 70 is max
    heap.extract(); // extract 70
    ASSERT_EQ(heap.peek().value_or(-1), 50); // 50 is next max
    ASSERT_EQ(heap.size(), 4);
}

