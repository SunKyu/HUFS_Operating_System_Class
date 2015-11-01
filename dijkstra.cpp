#include <iostream>
#include <queue>
using namespace std;
queue<int> path;
int d[5] = {0, };//distance 
int previous[5]  ={0,};
bool S[5];
bool Q[5];
int map[5][5] = {
    {0, 1, 1, 0, 0},
    {1, 0, 0, 2, 3},
    {1, 0, 0, 0, 5},
    {0, 2, 0, 0, 2},
    {0, 3, 5, 2, 0}
};

int weight(int u, int v){
    return map[u][v];
}

int min_dist(){
    int min_val = 9999;
    int index = -1;
    for (int i = 0 ; i<5; i++){
        if (Q[i]){
            for (int v =0; v<5; v++){
                if(map[v][i]<min_val&&Q[v] == false && map[v][i] != 0){
                    min_val = map[v][i];
                    d[i] = d[v] + map[v][i];
                    index  = i;
                }
            }
        }
    }
    cout<<"index : "<< index<<endl;
    return index;
}

void dijkstra(int s){
    for ( int v = 0; v < 5 ; v++){
        d[v] = 9999; //-1 mean infinity
        previous[v] = -1 ; //-1 mean undefined
        S[v] = false;
        Q[v] = true;
    }
    d[s] = 0;
    previous[s] = s;
    Q[s] = false;
    int u = 0;
    while (1){
        int count = 0 ;
        for ( auto i : Q){
            if (i == false){
                count ++;
            }
        }
        if (count == 5){
            break;
        }
        u = min_dist();
        Q[u] = false;
        for (int i = 0 ; i < 5; i++){
            if (Q[i] == true && map[u][i] !=0){
                int alt = d[u] + map[u][i];
                if (alt < d[i]){
                    d[i] = alt;
                    previous[i] = u;
                }
            }
        }
    }
}

int main (int argc, char * argv[]){
    for( int i = 0 ; i<5; i++){
        for (int j = 0; j<5; j++){
            cout<<map[i][j]<<" ";
        }
        cout <<endl;
    }
    dijkstra(3);
    int i = 2;

    while (1){
        cout<<"prve of "<<previous[i]<<endl;
        i = previous[i];
        if (i == -1){
            cout <<"break"<<endl;
            break;
        }
    }
}
