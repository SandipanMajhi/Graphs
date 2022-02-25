/**
 * @file graph_from_scratch.cpp
 * 
 * Building graph from scratch using a LinkedList for Adjacency list.
 * 
 * @author Sandipan Majhi
 * @brief 
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <list>
#include <time.h>

using namespace std;

class Node{
    public:
    int data, cost;
    Node *next;

    Node(int val, int c){
        this -> data = val;
        this -> next = NULL;
        this -> cost = c;
    }

    Node(int val){
        this -> data = val;
        this -> next = NULL;
        this -> cost = 0;
    }

    Node(){
        this -> data = 0;
        this -> cost = 0;
        this -> next = NULL;
    }
};

class LinkedList{
    public:

    Node *head;
    LinkedList(Node *h){
        this -> head = h;
    }
    LinkedList(){
        this -> head = NULL;
    }

    Node* deleteNode(Node *head, int val){
        Node *cur = search(head, val);
        if(cur == NULL){
            cout << "Node does not exist" << endl;
            return NULL;
        }else{
            Node *temp = head;
            while(temp -> next != cur){
                temp = temp -> next;
            }
            if(cur -> next == NULL){
                temp -> next = NULL;
            }else{
                temp -> next = cur -> next;
                cur -> next = NULL;
            }
        }
        return head;
    }

    Node* insert(Node *head, int val){
        if(head == NULL){
            return (new Node(val));
        }else
            head -> next = insert(head -> next, val);
        return head;
    }

    Node* search(Node *head, int val){
        if(head == NULL){
            return NULL;
        }else if(head -> data == val){
            return head ;
        }else
            return search(head -> next, val);
    }

    void printlist(Node *head){
        if(head != NULL)
            cout << head -> data << " ";
        
        if(head -> next != NULL)
            printlist(head -> next);
    }


};

class Vertex{
    public:
    int name;
    LinkedList *l;

    Vertex(int n){
        this -> name = n;
        this ->l = new LinkedList();
    }

    Vertex(){
        this -> name = -1;
        this -> l = new LinkedList();
    }
};

class Graph{
    public:
    int N;
    Vertex *v;
    int *visited;

    Graph(int V){
        this -> N =  V;
        this -> v = new Vertex[V];

        for(int i = 0; i<V; i++){
            this -> v[i].name = i;
        }

        visited = new int[this -> N];
    }

    void make_visited_zero(){
        for (int i = 0; i< this -> N; i++){
            this -> visited[i] = 0;
        }
    }

    void addEdge(int start, int end, int wt){
        if(start < 0 || start  >= this -> N || end  < 0 || end >= this -> N){
            cout << "This edge cannot be added" << endl;
        }else{
            if(this -> v[start].l -> search (this -> v[start].l ->head, end) == NULL){
                this -> v[start].l ->head = this -> v[start].l -> insert(this -> v[start].l ->head,end);
                this -> v[start].l -> search(this -> v[start].l ->head, end) ->cost = wt; 
            }
        }
    }

    void addEdge(int start, int end){
        if(start < 0 || start  >= this -> N || end  < 0 || end >= this -> N){
            cout << "This edge cannot be added" << endl;
        }else{
            if(this -> v[start].l -> search (this -> v[start].l ->head, end) == NULL){
                this -> v[start].l ->head = this -> v[start].l -> insert(this -> v[start].l ->head,end);
            }
        }
    }

    void printGraph(){
        for(int i = 0; i < this -> N; i++){
            cout << this -> v[i].name << "-> ";
            if(this -> v[i].l -> head != NULL)
                this -> v[i].l -> printlist(this -> v[i].l -> head);
            cout << "\n";
        }
    }

    void BFS(){
        queue<Vertex> insq;
        insq.push(this -> v[0]);
        Vertex cur;

        while(!insq.empty()){
            cur = insq.front();
            insq.pop();

            if(!this -> visited[cur.name]){
                cout << cur.name << " ";
                Node *head = cur.l->head;

                while(head != NULL){
                    insq.push(this -> v[head -> data]);
                    head = head -> next;
                }

                this -> visited[cur.name] = 1;
            }
        }

    }

    void DFS(int start){
        this -> visited[start] = 1;
        cout << start << " ";
        LinkedList *connect = this -> v[start].l;

        Node *cur = connect -> head;

        while(cur != NULL){
            if(!visited[cur ->data])
                DFS(cur -> data);

            cur = cur -> next;
        }
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

    g -> printGraph();

    cout << "BFS Algorithm :" << endl;
    g -> make_visited_zero();
    g -> BFS();

    cout << "\n\n";

    cout << "DFS Algorithm :" << endl;
    g -> make_visited_zero();
    g -> DFS(0);



    return 0;
}