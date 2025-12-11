#include "maxheap.h"
#include <assert.h>

int main() {
	MaxHeap heap;
	maxheap_init(&heap);
	assert( maxheap_peek(&heap) == INT_MIN);	

	printf("-- Testing MaxHeap (size: %d) ---\n", MAX_HEAP_SIZE);
	maxheap_insert(&heap, 10);
	maxheap_insert(&heap, 5);
	maxheap_insert(&heap, 20);
	maxheap_insert(&heap, 15);
	maxheap_insert(&heap, 25);

	printf("Size after insert:  %d\n", heap.size);
	printf("Current max: %d\n", maxheap_peek(&heap));
	printf("Pop the max: %d  (expecting this: 25) \n", maxheap_extract(&heap));
	printf("Current max: %d\n", maxheap_peek(&heap));
	printf("Size after extract:  %d\n", heap.size);

	return 0;
}
