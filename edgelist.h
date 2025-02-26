/*
 * edgelist.h
 *
 *  Created on: Mar 30, 2023
 *      Author: trinh
 */

#ifndef EDGELIST_H_
#define EDGELIST_H_

typedef struct edge {
  int from;
  int to;
  int weight;
  struct edge *next;
} EDGE;

// your code document
typedef struct edgelist {
  int size;
  EDGE *start;
  EDGE *end;
} EDGELIST;

EDGELIST *new_edgelist();
void add_edge_end(EDGELIST *g, int from, int to, int weight);
void add_edge_start(EDGELIST *g, int from, int to, int weight);
int weight_edgelist(EDGELIST *g);
void display_edgelist(EDGELIST *g);
void clean_edgelist(EDGELIST **gp);

#endif /* EDGELIST_H_ */
