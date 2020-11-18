#include <iostream>
#include <string>
#include <queue>

using namespace std;
char floor[1000][1000];
int main(int argc, const char * argv[]) {
    int height,width,start_index;
    string str;
    cin>>height>>width;

    int k =0 ;
    int tree [(height-2)*(width-2)+1][7]; //index,x,y,right,left,down,up
    
    getline(cin,str);
    for (int i = 0; i < height; i++){
        getline(cin,str);
        strcpy(floor[i], str.c_str());
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
                    tree[k][4] = k-1;
                }
                else{
                    tree[k][4] = -1;
                }
                if(floor[i][j] == 'R'){
                    start_index = k;
                }
                k+=1;
            }
        }
    }
    
    for (int i = 0; i < k; i++){
        if(tree[i][1] == height-2){
            tree[i][5] = -1;
        }
        else if(floor[tree[i][1]+1][tree[i][2]] != '1'){
            for(int l = i+1; l <= i+width-2;l++){ //兩側1可扣：待更
                if((tree[l][1] == tree[i][1]+1) && (tree[l][2] == tree[i][2])){
                    tree[i][5] = l;
                    break;
                }
                else{
                    tree[i][5] = -1;
                }
            }
        }
        else{
            tree[i][5] = -1;
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
    
    
    
    
    
    for (int i = 0; i < k; i++){
        for (int j = 0; j < 7; j++){
            cout<<tree[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}
//
//  main.cpp
//  108060071
//
//  Created by Hanna on 2020/11/14.
//  Copyright © 2020 鄭佳渝. All rights reserved.
//

/*#include <iostream>
#include <string>
#include <stdio.h>



using namespace std;

class Graph
{// object: A nonempty set of vertices and a set of undirected edges.
public:
    virtual ~Graph() {}
    bool IsEmpty() const{return n == 0};
    int NumberOfVertices() const{return n};
    int NumberOfEdges() const{return e};
    virtual int Degree(int u) const = 0;
    virtual bool ExistsEdge(int u, int v) const = 0;

    virtual void InsertVertex(int v) = 0;
    virtual void InsertEdge(int u, int v) = 0;
    virtual void DeleteVertex(int v) = 0;
    virtual void DeleteEdge(int u, int v) = 0; // More graph operations...
protected:
    int n; // number of vertices
    int e; // number of edges
};

void Graph::DFS(void){
    visited = new bool[n]; // this is a data member of Graph fill(visited, visited+n, false);
    DFS(0); // start search at vertex 0
    delete [] visited;
}
void Graph::DFS(const int v){
    // visit all previously unvisited vertices that are adjacent to v
    output(v);
    visited[v]=true;
    for(each vertex w adjacent to v)
        if(!visited[w]) DFS(w);
}*/
/*
class BinaryTree;
class TreeNode{
public:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    string str;

    TreeNode():leftchild(0),rightchild(0),parent(0),str(""){};
    TreeNode(string s):leftchild(0),rightchild(0),parent(0),str(s){};

    friend class BinaryTree;
};

class BinaryTree{
public:
    TreeNode *root;         // 以root作為存取整棵樹的起點
    BinaryTree():root(0){};
    BinaryTree(TreeNode *node):root(node){};
};

int main() {
    // TreeNode instantiation
    TreeNode *nodeA = new TreeNode("A");
    TreeNode *nodeB = new TreeNode("B");
    TreeNode *nodeC = new TreeNode("C");
    TreeNode *nodeD = new TreeNode("D");
    TreeNode *nodeE = new TreeNode("E");
    TreeNode *nodeF = new TreeNode("F");
    TreeNode *nodeG = new TreeNode("G");
    TreeNode *nodeH = new TreeNode("H");
    TreeNode *nodeI = new TreeNode("I");

    // construct the Binary Tree
    nodeA->leftchild = nodeB; nodeA->rightchild = nodeC;
    nodeB->leftchild = nodeD; nodeB->rightchild = nodeE;
    nodeE->leftchild = nodeG; nodeE->rightchild = nodeH;
    nodeC->leftchild = nodeF; nodeF->rightchild = nodeI;

    BinaryTree T(nodeA);*/
