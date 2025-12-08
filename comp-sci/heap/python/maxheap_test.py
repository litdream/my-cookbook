import pytest
from maxheap import MaxHeap

def test_insert_and_peek():
    heap = MaxHeap()
    heap.insert(10)
    assert heap.peek() == 10
    heap.insert(20)
    assert heap.peek() == 20
    heap.insert(5)
    assert heap.peek() == 20

def test_extract():
    heap = MaxHeap()
    heap.insert(10)
    heap.insert(20)
    heap.insert(5)
    assert heap.extract() == 20
    assert heap.peek() == 10
    assert heap.extract() == 10
    assert heap.peek() == 5
    assert heap.extract() == 5
    assert heap.peek() is None

def test_extract_empty():
    heap = MaxHeap()
    assert heap.extract() is None

def test_extract_single_element():
    heap = MaxHeap()
    heap.insert(42)
    assert heap.extract() == 42
    assert heap.extract() is None
    assert heap.peek() is None

def test_size():
    heap = MaxHeap()
    assert heap.size() == 0
    heap.insert(10)
    assert heap.size() == 1
    heap.insert(20)
    assert heap.size() == 2
    heap.extract()
    assert heap.size() == 1
    heap.extract()
    assert heap.size() == 0

def test_peek_empty():
    heap = MaxHeap()
    assert heap.peek() is None

def test_insert_duplicates():
    heap = MaxHeap()
    heap.insert(10)
    heap.insert(20)
    heap.insert(10)
    assert heap.peek() == 20
    assert heap.extract() == 20
    assert heap.extract() == 10
    assert heap.extract() == 10

def test_insert_negative():
    heap = MaxHeap()
    heap.insert(-10)
    heap.insert(-5)
    heap.insert(-20)
    assert heap.peek() == -5
    assert heap.extract() == -5
    assert heap.peek() == -10

def test_large_number_of_insertions():
    heap = MaxHeap()
    for i in range(100):
        heap.insert(i)
    assert heap.peek() == 99
    assert heap.size() == 100
    for i in range(99, -1, -1):
        assert heap.extract() == i
    assert heap.size() == 0
    assert heap.peek() is None
    assert heap.extract() is None
