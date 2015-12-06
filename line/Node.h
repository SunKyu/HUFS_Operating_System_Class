#ifndef _NODE_H_
#define _NODE_H_
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

struct Node{
    int id;
    int dir[4];//0, 1, 2, 3 -> up, down, left, right vertex
};
struct Node node_arr[14];
void node_init();

#endif
