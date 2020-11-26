#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;
char floor[1000][1000];//輸入的地圖
int k =0 ;
int tree [996005][8]; //記錄不是1的index,x,y,right,down,left,up,經過次數
int height,width,start_index,life;
queue<int> qu;

bool check(int& ,int& ); //上下左右有無尚未經過的點
int pass_time_least(int); //經過次數最少次
void set_four_neighbor(); //上下左右節點紀錄
void push(int* ,int& ,int& ); //push路徑進去queue

int main(int argc, const char * argv[]) {
    ifstream file(argv[1], ios::in); //讀檔
    file>>height>>width>>life;
    string str;
    getline(file, str);//先吃一行
    
    for (int i = 0; i < height; i++){
        getline(file, str);
        strcpy(floor[i], str.c_str());
    }
    set_four_neighbor();
    
    int route[life+1]; //儲存路徑:點的index
    int step=0; //紀錄步數
    
    route[0] = start_index; //第一步從起點開始
    int vertex = start_index;
    tree[start_index][7] = 1; //標記起點已走過
    int r = 1; //路徑從1起始
    
    bool con=true;
    
    
    while(con){
        bool con=false;
        if(check(vertex,r)){ //上下左右有無尚未經過的點
            vertex=pass_time_least(vertex); //上下左右都經過過了-->找經歷次數最少的
        }
        tree[vertex][7]+=1; //經過次數+1
        route[r] = vertex; //紀錄路過的index
        
        for(int i = 0; i<k;i++){
            if(tree[i][7]==0){ //任何一個點沒被經過就得繼續while
                con=true;
                break;
            }
        }
        
        if(r*2==life ||r*2==life-1){ //走的步數*2接近或等於電池
            push(&route[0],r,step);
            r=0;
            route[0] = start_index;
            vertex = start_index;
        }
        if(!con){ //所有點都被經過過了
            push(&route[0],r,step);
            break;
        }
        r+=1;
    }
    fstream file_out;
    file_out.open("final.path", ios::out);
    file_out<<step<<endl;
    file_out<<tree[start_index][1]<<" "<<tree[start_index][2]<<endl;
    for(int i=0;i<step;i++){
        int e=qu.front();
        qu.pop();
        file_out<<tree[e][1]<<" "<<tree[e][2]<<endl;
    }
    return 0;
}
void push(int* route,int &r,int &step){
    for(int j=1;j<=r;j++){
        qu.push(route[j]); //印出此趟路徑去程
        step+=1;
    }
    for(int j=r-1;j>=0;j--){
        qu.push(route[j]); //印出此趟路徑回程
        step+=1;
    }
}

bool check(int &v,int &r){
    for(int i = 3; i < 7; i++){ //檢查node的上下左右
        if(tree[v][i] != -1){ //如果此方位有路
            if(tree[tree[v][i]][7] == 0){ //如果沒有被經過過
                v = tree[v][i]; //vertex改由此點開始
                return false;
            }
        }
    }
    return true; //上下左右都經過過
}
int pass_time_least(int v){
    int min_7 = 99999999;
    int min_index_7 = 0;
    for(int i = 3; i < 7; i++){//上下左右經過次數
        if(tree[v][i] != -1){
            if(tree[tree[v][i]][7]<min_7){
                    min_7 = tree[tree[v][i]][7];
                    min_index_7= i;
                    
            }
        }
    }
    return tree[v][min_index_7]; //回傳最少經過的node的index
}
void set_four_neighbor(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if(floor[i][j] != '1'){ //將不是1的記錄到tree
                tree[k][0] = k; //編號
                tree[k][1] = i; //x座標
                tree[k][2] = j; //y座標
                if(floor[i][j+1] != '1'){
                    tree[k][3] = k+1; //右邊node的index
                }
                else{
                    tree[k][3] = -1;
                }
                if(floor[i][j-1] != '1'){
                    tree[k][5] = k-1; //左邊node的index
                }
                else{
                    tree[k][5] = -1;
                }
                if(floor[i][j] == 'R'){
                    start_index = k;
                }
                tree[k][7]=0; //有無次數
                k+=1;
            }
        }
    }
    for (int i = 0; i < k; i++){
        if(tree[i][1] == height-2){ //最下排node
            tree[i][4] = -1; //下方node的index
        }
        else if(floor[tree[i][1]+1][tree[i][2]] != '1'){
            for(int l = i+1; l <= i+width-2;l++){
                if((tree[l][1] == tree[i][1]+1) && (tree[l][2] == tree[i][2])){
                    tree[i][4] = l;
                    break;}
                else{
                    tree[i][4] = -1;
                }
            }
        }
        else{
            tree[i][4] = -1;
        }
        if(tree[i][1] == 1){ //最上排node
            tree[i][6] = -1; //上方node的index
        }
        else if(floor[tree[i][1]-1][tree[i][2]] != '1'){
            for(int l = i-1; l >= i-width+2; l--){
                if((tree[l][1] == tree[i][1]-1) && (tree[l][2] == tree[i][2])){
                    tree[i][6] = l;
                    break;
                }
                else{
                    tree[i][6] = -1;
                }
            }
        }
        else{
            tree[i][6] = -1;
        }
    }
}
