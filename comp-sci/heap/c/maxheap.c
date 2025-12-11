#include "maxheap.h"

//
// Private functions for convenience.
//
static size_t  get_parent_idx(size_t child_idx) {
	if (child_idx == 0)
		return 0;
	return (child_idx -1) /2;
}

static size_t  get_left_child_idx(size_t par_idx) {
	return 2 * par_idx + 1;
}

static size_t  get_right_child_idx(size_t par_idx) {
	return 2 * par_idx + 2;
}


static void heapify_up(MaxHeap *heap, size_t child_idx) {
	while (child_idx > 0) {
		size_t par_idx = get_parent_idx(child_idx);
		int *hdata = heap->data;
		if (hdata[child_idx] > hdata[par_idx]) {
			int tmp          = hdata[child_idx];
			hdata[child_idx] = hdata[par_idx];
			hdata[par_idx]   = tmp;

			child_idx = par_idx;
		} else {
			break;
		}
	}
}

static void heapify_down(MaxHeap *heap, size_t par_idx) {
	while (par_idx < heap->size) {
		size_t  largest_idx     = par_idx;
		size_t  left_child_idx  = get_left_child_idx(par_idx);
		size_t  right_child_idx = get_right_child_idx(par_idx);

		// find max out of 3.
		int *hdata = heap->data;
		if ( left_child_idx < heap->size && hdata[left_child_idx] > hdata[largest_idx]) 
			largest_idx = left_child_idx;
		if ( right_child_idx < heap->size && hdata[right_child_idx] > hdata[largest_idx])
			largest_idx = right_child_idx;

		if ( largest_idx == par_idx )
			break;    // heap property met.  no more traverse
		
		// swap and continue
		int tmp              = hdata[par_idx];
		hdata[par_idx]       = hdata[largest_idx];
		hdata[largest_idx ]  = tmp;

		par_idx = largest_idx;
	}
}


// Public methods

void maxheap_init(MaxHeap *heap) {
	if (heap != NULL) {
		heap->size = 0;
	}
}

int maxheap_insert(MaxHeap *heap, int item) {
	if (heap == NULL) return -1;

	if (heap->size >= MAX_HEAP_SIZE) {
		fprintf(stderr, "Error: MaxHeap is full (size: %d)\n", heap->size);
		return -1;   // heap is full.
	}

	heap->data[heap->size] = item;
	heapify_up(heap, heap->size);
	heap->size++;

	return 0;
}

int maxheap_peek(MaxHeap *heap) {
	if (heap->size == 0) {
		return INT_MIN;    // invalid value.
	}
	return heap->data[0];
}

int maxheap_extract(MaxHeap *heap) {
	if (heap->size == 0) {
		return INT_MIN;   // invalid value.
	}

	int max_val = heap->data[0];   // will return later.

	heap->data[0] = heap->data[ heap->size - 1];
	heap->size--;
	if (heap->size > 0) {
		heapify_down(heap, 0);
	}
	return max_val;
}
