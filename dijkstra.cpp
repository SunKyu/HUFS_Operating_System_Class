#include <iostream>
#include <queue>
using namespace std;
queue<int> path;
int d[14] = {0, };//distance 
int previous[14]  ={0,};
bool S[14];
bool Q[14];
int map[14][14] = {0, };

void init_map(int a){
    cout<<"initstat"<<endl;
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
    cout<<"instendl"<<endl;

    for( int i = 0; i <14 ; i++){
        for (int j = 0; j<14 ; j++){
            if(map[i][j]!=0){
                map[j][i] = map [i][j];
            }
        }
    }
}

int weight(int u, int v){
    return map[u][v];
}

int min_dist(){
    int min_val = 9999;
    int index = -1;
    for (int i = 0 ; i<14; i++){
        if (Q[i]){
            for (int v =0; v<14; v++){
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
    for ( int v = 0; v < 14 ; v++){
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
        if (count == 14){
            break;
        }
        u = min_dist();
        Q[u] = false;
        for (int i = 0 ; i < 14; i++){
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
    init_map(3);
    cout<<"ehfeefe\n"<<endl;
    for( int i = 0 ; i<14; i++){
        for (int j = 0; j<14; j++){
            cout<<map[i][j]<<" ";
        }
        cout <<endl;
    }
    dijkstra(13);
    int i = 4;

    while (1){
        cout<<"prve of "<<previous[i]<<endl;
        i = previous[i];
        if (i == -1){
            cout <<"break"<<endl;
            break;
        }
    }
}
