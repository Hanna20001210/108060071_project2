#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;
char floor[1000][1000];
int k =0 ;
int tree [996005][10]; //index,x,y,right,down,left,up,有無經過,經過次數,經過順序
int height,width,start_index,life;

bool check(int& ,int& );
int choose_the_earliest(int);
void set_four_neighbor();

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
    
    int route[life+1][2]; //儲存路徑
    int count = 1;
    int step=0;
    route[0][0] = start_index;
    int vertex = start_index;
    tree[start_index][7] = 1;
    queue<int> qu;
    int r = 1;
    bool con=true;
    while(con==true){
        bool con=false;
        if(check(vertex,r)){
            //cout<<vertex<<"四周點都被經過了"<<endl;
            vertex = choose_the_earliest(vertex);
            count = tree[vertex][7]-1;
            //cout<<"回去點"<<vertex<<endl;
        }
        tree[vertex][7]+=1;
        for(int i = 0; i<k;i++){
            if(tree[i][7]==0){
                con=true;
                break;
            }
        }
        if(con==false){
            for(int j=1;j<=r;j++){
                //cout<<route[j][0]<<" ";//<<route[j][1]<<" "<<route[j][2]<<endl;
                qu.push(route[j][0]);
                //cout<<tree[route[j][0]][1]<<" "<<tree[route[j][0]][2]<<endl;
                step+=1;
            }
            for(int j=r-1;j>=0;j--){
                //cout<<route[j][0]<<" ";//<<route[j][1]<<" "<<route[j][2]<<endl;
                qu.push(route[j][0]);
                //cout<<tree[route[j][0]][1]<<" "<<tree[route[j][0]][2]<<endl;
                step+=1;
            }
            break;
        }
        route[r][0] = vertex;
        route[r][1] = r*2;
        if(route[r][1]==life ||route[r][1]==life-1 || con==false){
            for(int j=1;j<=r;j++){
                //cout<<route[j][0]<<" ";//<<route[j][1]<<" "<<route[j][2]<<endl;
                qu.push(route[j][0]);
                //cout<<tree[route[j][0]][1]<<" "<<tree[route[j][0]][2]<<endl;
                step+=1;
            }
            for(int j=r-1;j>=0;j--){
                //cout<<route[j][0]<<" ";//<<route[j][1]<<" "<<route[j][2]<<endl;
                qu.push(route[j][0]);
                //cout<<tree[route[j][0]][1]<<" "<<tree[route[j][0]][2]<<endl;
                step+=1;
            }
            r=0;
            count=0;
            route[0][0] = start_index;
            vertex = start_index;
        }
        r+=1;
        count+=1;
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

bool check(int &v,int &r){
    for(int i = 3; i < 7; i++){
        //cout<<"看"<<v<<"的上下左右"<<endl;
        if(tree[v][i] != -1){
            if(tree[tree[v][i]][7] == 0){
                //cout<<tree[v][i]<<"尚未被經過"<<endl;
                tree[tree[v][i]][7] +=1;
                //cout<<"令"<<tree[v][i]<<"為新的起點"<<endl;
                v = tree[v][i];
                return false;
            }
        }
    }
    return true;
}
int choose_the_earliest(int v){
    int min_7 = 99999999;
    int min_index_7;
    for(int i = 3; i < 7; i++){
        //cout<<"看"<<v<<"的上下左右"<<endl;
        if(tree[v][i] != -1){
            if(tree[tree[v][i]][7]<min_7){
                    min_7 = tree[tree[v][i]][7];
                    min_index_7= i;
                    
            }
        }
    }
    return tree[v][min_index_7];
}
void set_four_neighbor(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if(floor[i][j] != '1'){
                tree[k][0] = k;
                tree[k][1] = i;
                tree[k][2] = j;
                if(floor[i][j+1] != '1'){
                    tree[k][3] = k+1; //右邊一個node的index
                }
                else{
                    tree[k][3] = -1;
                }
                if(floor[i][j-1] != '1'){
                    tree[k][5] = k-1;
                }
                else{
                    tree[k][5] = -1;
                }
                if(floor[i][j] == 'R'){
                    start_index = k;
                }
                tree[k][7]=0;
                tree[k][8]=0;
                tree[k][9]=0;
                k+=1;
            }
        }
    }
    for (int i = 0; i < k; i++){
        if(tree[i][1] == height-2){
            tree[i][4] = -1;
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
        if(tree[i][1] == 1){
            tree[i][6] = -1;
        }
        else if(floor[tree[i][1]-1][tree[i][2]] != '1'){
            for(int l = i-1; l >= i-width+2; l--){ //兩側1可扣：待更
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
