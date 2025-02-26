/*
 * heap.c
 *
 *  Created on: Jul 22, 2023
 *      Author: trinh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

HEAP *new_heap(int capacity){
// your implementation
	HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
	hp->capacity = capacity;
	hp->size = 0;
	hp->hna = (HNODE *) malloc(sizeof(HNODE) * capacity);
	return hp;
}

void insert(HEAP *heap, HNODE new_node){
// your implementation
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;
		void *temp = realloc(heap->hna, sizeof(HNODE) * heap->capacity);
		if (temp){
			heap->hna = temp;
		}else{
			temp = malloc(sizeof(HNODE) * heap->capacity);
			if (temp){
				memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
				free(heap->hna);
				heap->hna = temp;
			}else{
				printf("array resize failed\n");
			}
		}
	}
}

HNODE extract_min(HEAP *heap){
// your implementation
	if (heap->size == 0) {
		HNODE empty_node = {0};
		return empty_node;
	}
	HNODE min_node = heap->hna[0];
	heap->size--;
	if (heap->size > 0) {
		heap->hna[0] = heap->hna[heap->size];
		int index = 0;
		while (2 * index + 1 < heap->size) {
		    int left = 2 * index + 1;
		    int right = 2 * index + 2;
		    int smallest = left;
		    if (right < heap->size && heap->hna[right].key < heap->hna[left].key) {
		        smallest = right;
		    }
		    if (heap->hna[index].key > heap->hna[smallest].key) {
		        HNODE temp = heap->hna[index];
		        heap->hna[index] = heap->hna[smallest];
		        heap->hna[smallest] = temp;
		        index = smallest;
		    } else {
		        break;
		    }
		}
	}
	return min_node;
}

int change_key(HEAP *heap, int index, KEYTYPE new_key){
// your implementation
	if (heap == NULL || index < 0 || index >= heap->size) {
		return 1;
	}
	heap->hna[index].key = new_key;
	int parent = (index - 1) / 2;
	while (index > 0 && heap->hna[parent].key > heap->hna[index].key) {
		HNODE tmp = heap->hna[parent];
		heap->hna[parent] = heap->hna[index];
		heap->hna[index] = tmp;

		index = parent;
		parent = (index - 1) / 2;
	}
}

int find_data_index(HEAP *heap, DATA data) {
// your implementation
	for (int i = 0; i < heap->size; i++) {
		if (heap->hna[i].data == data) {
		    return i;
		}
	}
	return -1;
}

int cmp(KEYTYPE a, KEYTYPE b) {
// your implementation
	int r = 0;
	if (a < b) r = -1;
	else if (a > b) r = 1;
	return r;
}
