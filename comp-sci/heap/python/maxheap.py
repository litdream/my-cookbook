class MaxHeap:
    def __init__(self):
        self.heap = []

    def insert(self, item):
        """New data is inserted.
        At the end of the heap, and heapify up.
        """
        new_idx = len(self.heap)
        self.heap.append(item)
        self.heapify_up(new_idx)

    def heapify_up(self, child_idx):
        par_idx = (child_idx -1) // 2

        # Note:  The second term: self.heap[0] > self.heap[0] is the termination condition.
        if par_idx >=0 and self.heap[child_idx] > self.heap[par_idx]:
            # swap and up
            self.heap[child_idx], self.heap[par_idx] = self.heap[par_idx], self.heap[child_idx]
            self.heapify_up(par_idx)

    def peek(self):
        if len(self.heap) >0:
            return self.heap[0]
        return None

    def size(self):
        return len(self.heap)


    def extract(self):
        """Remove the MaxValue (max-heap)
        Root is removed, old-tail-value is pushed-down from the root.
        """
        if len(self.heap) == 0:
            return None
        if len(self.heap) == 1:
            return self.heap.pop()

        rtn = self.heap[0]
        self.heap[0] = self.heap.pop()
        self.heapify_down(0)
        return rtn

    def heapify_down(self, par_idx):
        largest_idx = par_idx
        left_child_idx, right_child_idx = 2*par_idx +1, 2*par_idx +2

        # check boundaries together, and pick largest of 3
        if left_child_idx < len(self.heap) and self.heap[left_child_idx] > self.heap[largest_idx]:
            largest_idx = left_child_idx
        if right_child_idx < len(self.heap) and self.heap[right_child_idx] > self.heap[largest_idx]:
            largest_idx = right_child_idx

        # If bubbled, fix the structure:  largest_idx is the larger of the 2 of children
        if largest_idx != par_idx:
            self.heap[par_idx], self.heap[largest_idx] = self.heap[largest_idx], self.heap[par_idx]
            self.heapify_down(largest_idx)

        
