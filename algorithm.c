/*
 * algorithm.c
 *
 *  Created on: Mar 30, 2023
 *      Author: trinh
 */

#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "heap.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
// your implementation
	if (g == NULL) return NULL;
	int i, heapindex, u, n = g->order, T[n], parent[n];
	for (i = 0; i < n; i++)
		T[i] = 0; // T[] represents nodes in current tree
	for (i = 0; i < n; i++)
		parent[i] = -1; // parent[i] represents parent of i
	HNODE hn; // temp hash note variable
	HEAP *h = new_heap(4); // heap for finding minimum weight edge

	// set the first node of current tree T from start
	T[start] = 1;
	// for each neighbor, add corresponding heap node into heap
	ADJNODE *temp = g->nodes[start]->neighbor;
	while (temp) {
		hn.key = temp->weight;
		hn.data = temp->nid;
		insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	// create EDGELIST object to hold MST
	EDGELIST *mst = new_edgelist();
	// the main loop the Prim’s algorithm
	while (h->size > 0) {
		hn = extract_min(h); // get the minimum node, time
		i = hn.data;
		T[i] = 1; // add i to current tree
		add_edge_end(mst, parent[i], i, hn.key); // add to MST
	    // update the keys of neighbors of the newly added node
		temp = g->nodes[i]->neighbor;
		while (temp) {
			heapindex = find_data_index(h, temp->nid);
			if (heapindex >= 0) {
				if (T[temp->nid] == 0 && temp->weight < h->hna[heapindex].key) {
					change_key(h, heapindex, temp->weight);
					T[temp->nid] = i;
				}
			} else {
				if (T[temp->nid] == 0) {
					hn.key = temp->weight;
					hn.data = temp->nid;
					insert(h, hn);
					parent[temp->nid] = i;
				}
			}
			temp = temp->next;
		}
	}
	return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
// your implementation
	if (!g) return NULL;
	EDGELIST *spt = new_edgelist();
	int i, heapindex, u, n = g->order;
	int T[n], parent[n], label[n];
	HNODE hn;
	for (i = 0; i < n; i++) {
		T[i] = 0; label[i] = 9999;
	}
	HEAP *h = new_heap(4);
	ADJNODE *temp = g->nodes[start]->neighbor;
	label[start] = 0;
	T[start] = 1;
	u=start;
	while (temp) {
		hn.key = temp->weight+label[start];
		hn.data = temp->nid;
		insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	while (h->size > 0) {
		hn = extract_min(h);
		u = hn.data; T[u] = 1;
		label[u] = hn.key;
		add_edge_end(spt, parent[u], u, label[u]-label[parent[u]]); // label[u]-label[parent[u] is weight of newly added edge
	}
}


EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
// your implementation
	if (!g) return NULL;
	EDGELIST *spt = new_edgelist();
	int i, heapindex, u, n = g->order;
	int T[n], parent[n], label[n];
	HNODE hn;
	for (i = 0; i < n; i++) {
		T[i] = 0;
		label[i] = 9999;
	}
	HEAP *h = new_heap(4);
	ADJNODE *temp = g->nodes[start]->neighbor;
	label[start] = 0;
	T[start] = 1;
	u=start;
	while (temp) {
		hn.key = temp->weight+label[start];
		hn.data = temp->nid;
		insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	while (h->size > 0) {
		hn = extract_min(h);
		u = hn.data; T[u] = 1;
		label[u] = hn.key;
		if ( u == end) break;
	}
	EDGELIST *sp = new_edgelist();
	i = end;
	while (1) {
		if (i == start) break;
		add_edge_start(sp, parent[i], i, label[i]-label[parent[i]]);
		i = parent[i];
	}
	return sp;
}
