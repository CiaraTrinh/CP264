/*
 * edgelist.c
 *
 *  Created on: Jul 25, 2023
 *      Author: trinh
 */

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST *new_edgelist() {
// your implementation
	EDGELIST *p=malloc(sizeof(EDGELIST));
	//initial setting
	p->size=0;
	p->start=NULL;
	p->end=NULL;
	return p;
}

void add_edge_end(EDGELIST *g, int from, int to, int weight) {
// your implementation
	EDGE *p=malloc(sizeof(EDGE));
	p->from=from;
	p->to=to;
	p->weight=weight;
	p->next=NULL;
	if(g->end){
		g->end->next=p;
	}else{
		g->start=p;
	}
	g->size++;
	g->end=p;
}

void add_edge_start(EDGELIST *g, int from, int to, int weight) {
// your implementation
	EDGE *p=malloc(sizeof(EDGE));
	p->from=from;
	p->to=to;
	p->weight=weight;
	p->next=g->start;
	if(!g->start){
		g->end=p;
	}
	g->size++;
	g->start=p;
}

int weight_edgelist(EDGELIST *g) {
// your implementation
	int e=0;
	EDGE *p=g->start;
	while(p){
		e+=p->weight;
		p=p->next;
	}
	return e;
}

void clean_edgelist(EDGELIST **gp) {
  EDGELIST *g = *gp;
  EDGE *temp, *p = g->start;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  free(g);
  *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
  if (g == NULL) return;
  printf("size:%d\n", g->size);
  printf("(from to weight):");
  EDGE *p = g->start;
  while (p) {
    printf("(%d %d %d) ", p->from, p->to, p->weight);
    p = p->next;
  }
}
