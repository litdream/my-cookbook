#!/usr/bin/env python3

import os
import sys

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def push(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return

        # push
        cur = self.head
        while cur.next is not None:
            cur = cur.next
        cur.next = new_node

        
    def pop(self):
        if not self.head:
            return None
        
        # Special case:  Only one node to make list empty after pop.
        if self.head.next is None:
            val = self.head.data
            self.head = None
            return val

        # pop and re-link
        cur = self.head
        while cur.next.next:
            cur = cur.next
            
        val = cur.next.data
        cur.next = None
        return val

    
    def size(self):
        count = 0
        cur = self.head
        while cur:
            count += 1
            cur = cur.next
        return count

    def min(self):
        if not self.head:
            return None
        
        min_val = self.head.data
        cur = self.head.next
        while cur:
            if cur.data < min_val:
                min_val = cur.data
            cur = cur.next
        return min_val

    def max(self):
        if not self.head:
            return None
        
        max_val = self.head.data
        cur = self.head.next
        while cur:
            if cur.data > max_val:
                max_val = cur.data
            cur = cur.next
        return max_val

    def print_list(self):
        elms = []
        cur = self.head
        while cur:
            elms.append(str(cur.data))
            cur = cur.next
        print(" -> ".join(elms))

    def sort(self):
        if not self.head or not self.head.next:
            return

        list_size = self.size()
        
        # Bubble sort 
        for i in range(list_size):
            cur = self.head
            for j in range(list_size - i - 1):
                if cur.data > cur.next.data:
                    cur.data, cur.next.data = cur.next.data, cur.data
                cur = cur.next

