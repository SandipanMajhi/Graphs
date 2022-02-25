/**
 * @file graph_list.cpp
 * @author Sandipan Majhi
 * @brief Graph using list stl in C++
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <queue>

using namespace std;

class Vertex{
    public:
    int name, outdeg, indeg;
    list<pair<int,int>> l;
    Vertex(int n){
        this -> name = n;
        this -> outdeg = 0;
        this -> indeg  = 0;
    }

    Vertex(){
        this -> name = -1;
        this -> outdeg = 0;
        this -> indeg  = 0;
    }
};

class Graph{
    public:

    int N;
    Vertex *v;
    int *visited;
    int *color;

    Graph(int V){
        this -> N = V;
        this -> v = new Vertex[V];
        this -> visited = new int[V];
        this -> color = new int[V];

        for(int i = 0; i< V; i++){
            this -> v[i].name = i;
            this -> color[i] = 0; // all are white
        }

        for(int i = 0; i< V; i++){
            this -> visited[i] = 0;
        }
    }

    void make_visited_zero(){
        for(int i = 0; i< this -> N; i++){
            this -> visited [i] = 0;
        }
    }

    void addEdge(int start, int end){
        if(start < 0 || start > this -> N || end < 0 || end > this -> N){
            cout << "Unable to form edge" << endl;
        }else{
            this -> v[start].l.push_back(pair<int, int>(end,0));
        }
    }

    void addEdge(int start, int end, int cost){
        if(start < 0 || start > this -> N || end < 0 || end > this -> N){
            cout << "Unable to form edge" << endl;
        }else{
            this -> v[start].l.push_back(pair<int, int>(end,cost));
        }
    }

    void BFS(int start){
        list<pair<int,int>> :: iterator itr;
        queue<int> insq;
        insq.push(start);
        int node;

        while(!insq.empty()){
            node = insq.front();
            insq.pop();

            if(!this -> visited[node]){
                cout << node << " ";
                this -> visited[node] = 1;
                for(itr = this -> v[node].l.begin(); itr != this -> v[node].l.end(); ++itr){
                    insq.push(itr -> first);
                }
            } 
        }
    }

    void DFS(int node){
        this -> visited[node] = 1;
        cout << node << " ";
        list<pair<int, int>> :: iterator itr;

        for(itr = this -> v[node].l.begin(); itr != this -> v[node].l.end(); ++itr){
            if(!visited[itr -> first])
                DFS(itr-> first);
        }
    }

    void printgraph(){
        list<pair<int,int>> :: iterator itr;

        for(int i = 0; i< this -> N ; i++){
            cout << i << "->";
            for(itr = this->v[i].l.begin(); itr != this->v[i].l.end(); ++itr){
                cout << itr -> first << " ";
            }

            cout << "\n";
        }
    }

    void determine_degree(){
        list<pair<int,int>> :: iterator itr;

        for(int i = 0; i< this -> N; i++){
            for(itr = this -> v[i].l.begin(); itr != this -> v[i].l.end(); ++itr){
                this ->v[i].outdeg++;
                this -> v[itr -> first].indeg++;
            }
        }
    }

    void print_degree(){
        determine_degree();
        for(int i = 0; i< this -> N; i++){
            cout << i << " " << this -> v[i].outdeg - this -> v[i].indeg << endl;
        }
    }

    void make_white(){
        for(int i = 0; i< this -> N; i++){
            this -> color[i] = 0;
        }
    }

    int iscycle(int node){
        list<pair<int, int>> :: iterator itr;
        this -> color[node] = 1;

        for(itr = this-> v[node].l.begin(); itr != this -> v[node].l.end(); itr++){

            if(this -> color[itr -> first] == 0){
                if(iscycle(itr -> first))
                    return 1;
            }else if(this -> color[itr -> first] == 1){
                return 1;
            }
        }
        this -> color[itr -> first] = 2;
        return 0;
    }

};

int main(){
    srand(time(0));
    Graph *g = new Graph(10);

    (*g).addEdge(0,2);
    (*g).addEdge(0,4);
    (*g).addEdge(9,1);
    (*g).addEdge(3,4);
    (*g).addEdge(2,5);

    for(int i = 0; i<20 ;i++){
        int start = rand() % 10;
        int end = rand() % 10;

        (*g).addEdge(start, end);
    }

    (*g).printgraph();

    cout << "BFS algorithm : " << endl;
    (*g).make_visited_zero();
    (*g).BFS(0);

    cout << "\nDFS algorithm : " << endl;
    (*g).make_visited_zero();
    (*g).DFS(0);

    cout << "\nPrint Degrees : " << endl;
    (*g).print_degree();

    cout << "\nFind Cycle : ";
    cout << (*g).iscycle(0);
    cout << endl;


    return 0;
}
