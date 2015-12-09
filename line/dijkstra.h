#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <stdio.h>
#include "stack.h"

int prev[14];//previous of each node
// 0 is unvisited vertex
// 1 is visited vertex  so 0 is in the set Q
int map[14][14];

void init_map();

void Dijkstra(int source); // source is start node
void dijkstra_run(int start, int flag, struct stack* st);
#endif
