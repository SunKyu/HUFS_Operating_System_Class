#include "dijkstra.h"

void init_map(){
    int i = 0;
    int j = 0;
    map[0][1] = 10;
    map[1][2] = 10;
    map[2][3] = 33;
    map[2][5] = 33;
    map[3][4] = 50;
    map[4][7] = 33;
    map[5][6] = 50;
    map[6][7] = 33;
    map[6][8] = 33;
    map[6][12] = 50;
    map[7][9] = 25;
    map[8][13] = 50;
    map[9][10] = 16;
    map[10][11] = 25;
    map[11][12] = 49;
    map [12][13] = 33;

    for(  i = 0; i <14 ; i++){
        for ( j = 0; j<14 ; j++){
            if(map[i][j]!=0){
                map[j][i] = map [i][j];
            }
            else{
                map[i][j] = 999;
                map[j][i] = 999;
            }
        }
    }
}

void Dijkstra(int source){ // source is start node
    int dist[14] = {0, };//distance
    dist[source] = 0;
    int Q[14] = {0, }; //that has the least dist[u] value
    int flag  = 0; //check Q's state (empty or not)
    int u = source;
    int i = 0;
    int j = 0;
    int v = 0;
    /*
     *intializeing for dikstra
     */
    for( i = 0; i<14; i++){
        dist[i] = 999;
    }
    dist[source] = 0;
    //main loop
    while(!flag){//check Q is empty(flag = 0 is not empty)
        int count = 0;
        for (  i = 0 ; i<14; i++){
            if (Q[i] == 1)
                count ++;
        }
        if (count == 14){
            flag = 1;//Q is empty
            continue;
        }
        //check first u
        //firsttime, source will be selected to u
        if ( Q[source] == 0){
            u = source;
            Q[u] = 1;
        }
        else{ //find the min node in Q set
            int min = 999;
            int index;
            for(  i = 0; i <14; i++){
                for ( j = 0; j<14 ; j++){
                    if(map[i][j]<min && Q[i] ==0){
                        min = map[i][j];
                        index = i;
                    }
                }
            }
            u = index;
            Q[u] = 1; //remove u from set Q
        }
        for ( v = 0; v<14; v++){
            int alt = 0;
             if(map[u][v] != 999 && Q[v] == 0){
                alt = dist[u] + map[u][v];
                if (alt < dist[v]){
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }
}

struct stack dijkstra_run(int start){
    struct stack s;
    stack_init(&s);
    init_map();
    Dijkstra(start);
    int end = 13;
    stack_push(&s, end);
    //find path
    while(end != 0){
        stack_push(&s, prev[end]);
        end = prev[end];
    }
    stack_push(&s, prev[end]);
    stack_print(&s);
    return s;
}

