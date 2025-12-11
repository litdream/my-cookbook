#ifndef RAY_MAXHEAP_H
#define RAY_MAXHEAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>   // INT_MIN

#define MAX_HEAP_SIZE  100

typedef struct {
	int data[MAX_HEAP_SIZE];
	size_t  size;
} MaxHeap;


// Zero the init heap
void maxheap_init(MaxHeap *heap);

// Methods
int maxheap_insert(MaxHeap *heap, int item);
int maxheap_peek(MaxHeap *heap);
int maxheap_extract(MaxHeap *heap);

#ifdef __cplusplus
}
#endif

#endif // RAY_MAXHEAP_H
