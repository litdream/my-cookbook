# Gemini Generated this unittest

import pytest
from linkedlist import LinkedList

@pytest.fixture
def empty_list():
    """Fixture for an empty linked list."""
    return LinkedList()

@pytest.fixture
def filled_list():
    """Fixture for a list populated with some data [10, 5, 30, 2]."""
    ll = LinkedList()
    ll.push(10)
    ll.push(5)
    ll.push(30)
    ll.push(2)
    return ll

def test_initialization(empty_list):
    """Test that a new list is empty."""
    assert empty_list.head is None
    assert empty_list.size() == 0

def test_push_and_size(empty_list):
    """Test pushing elements and checking size updates."""
    empty_list.push(1)
    assert empty_list.size() == 1
    assert empty_list.head.data == 1
    
    empty_list.push(2)
    assert empty_list.size() == 2
    # Verify traversal reaches end
    assert empty_list.head.next.data == 2

def test_pop_filled(filled_list):
    """Test popping from a populated list."""
    # List is [10, 5, 30, 2]
    val = filled_list.pop()
    assert val == 2
    assert filled_list.size() == 3
    
    val = filled_list.pop()
    assert val == 30
    assert filled_list.size() == 2

def test_pop_single():
    """Test popping the only element in a list."""
    ll = LinkedList()
    ll.push(99)
    val = ll.pop()
    assert val == 99
    assert ll.size() == 0
    assert ll.head is None

def test_pop_empty(empty_list):
    """Test popping from an empty list returns None."""
    assert empty_list.pop() is None

def test_min_max(filled_list):
    """Test min and max methods on populated list."""
    # List is [10, 5, 30, 2]
    assert filled_list.min() == 2
    assert filled_list.max() == 30

def test_min_max_empty(empty_list):
    """Test min and max on empty list return None."""
    assert empty_list.min() is None
    assert empty_list.max() is None

def test_sort(filled_list):
    """Test sorting the list."""
    # Before: [10, 5, 30, 2]
    filled_list.sort()
    
    # After: [2, 5, 10, 30]
    assert filled_list.head.data == 2
    assert filled_list.head.next.data == 5
    assert filled_list.head.next.next.data == 10
    assert filled_list.head.next.next.next.data == 30

def test_sort_empty_and_single(empty_list):
    """Test sort handles empty and single-element lists without error."""
    # Empty
    empty_list.sort()
    assert empty_list.head is None
    
    # Single element
    empty_list.push(1)
    empty_list.sort()
    assert empty_list.head.data == 1

def test_print_list(filled_list, capsys):
    """Test the print output format."""
    filled_list.print_list()
    captured = capsys.readouterr()
    assert captured.out.strip() == "10 -> 5 -> 30 -> 2"
