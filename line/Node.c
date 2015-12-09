#include "Node.h"
//up, down, left, right
void node_init(){
    int i  =0 ;
    for (i = 0; i< 14; i++){
        node_arr[i].id  =i ;
    }
    node_arr[0].dir[0] = 1;
    node_arr[0].dir[1] = 0;
    node_arr[0].dir[2] = 0;
    node_arr[0].dir[3] = 0;

    node_arr[1].dir[0] = 0;
    node_arr[1].dir[1] = 0;
    node_arr[1].dir[2] = 2;
    node_arr[1].dir[3] = 0;

    node_arr[2].dir[0] = 5;
    node_arr[2].dir[1] = 3;
    node_arr[2].dir[2] = 0;
    node_arr[2].dir[3] = 0;

    node_arr[3].dir[0] = 2;
    node_arr[3].dir[1] = 0;
    node_arr[3].dir[2] = 4;
    node_arr[3].dir[3] = 0;

    node_arr[4].dir[0] = 7;
    node_arr[4].dir[1] = 0;
    node_arr[4].dir[2] = 0;
    node_arr[4].dir[3] = 0;

    node_arr[5].dir[0] = 0;
    node_arr[5].dir[1] = 2;
    node_arr[5].dir[2] = 6;
    node_arr[5].dir[3] = 0;

    node_arr[6].dir[0] = 8;
    node_arr[6].dir[1] = 7;
    node_arr[6].dir[2] = 12;
    node_arr[6].dir[3] = 5;

    node_arr[7].dir[0] = 6;
    node_arr[7].dir[1] = 4;
    node_arr[7].dir[2] = 9;
    node_arr[7].dir[3] = 0;

    node_arr[8].dir[0] = 0;
    node_arr[8].dir[1] = 6;
    node_arr[8].dir[2] = 13;
    node_arr[8].dir[3] = 0;

    node_arr[9].dir[0] = 0;
    node_arr[9].dir[1] = 10;
    node_arr[9].dir[2] = 0;
    node_arr[9].dir[3] = 7;

    node_arr[10].dir[0] = 9;
    node_arr[10].dir[1] = 0;
    node_arr[10].dir[2] = 11;
    node_arr[10].dir[3] = 0;

    node_arr[11].dir[0] = 12;
    node_arr[11].dir[1] = 0;
    node_arr[11].dir[2] = 0;
    node_arr[11].dir[3] = 10;

    node_arr[12].dir[0] = 13;
    node_arr[12].dir[1] = 11;
    node_arr[12].dir[2] = 0;
    node_arr[12].dir[3] = 6;

    node_arr[13].dir[0] = 0;
    node_arr[13].dir[1] = 12;
    node_arr[13].dir[2] = 0;
    node_arr[13].dir[3] = 8;
}



