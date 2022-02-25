#include <iostream>
#include <cstdlib>
#include <time.h>
#include <list>
#include <queue>

using namespace std;

class Node{
    public:
    int data;
    list<int> l;

    Node(int name){
        this -> data = name;
    }

    Node(){

    }
};

class Graph{
    public:
    int V;
    Node *v;
    int *visited , *color;

    Graph(int N){
        this -> V = N;
        v = new Node[N];
        
        for(int i = 0; i< N; i++){
            v[i].data = i;
        }

        this -> visited = new int[N];
        this -> color = new int[N];
        for(int i = 0; i< N; i++){
            this -> visited[i] = 0;
            this -> color[i] = 0;
        }
    }

    void make_visited_zero(){
        for(int i = 0; i< this -> V; i++)
            this -> visited[i] = 0;
    }

    void make_color_white(){
        for(int i = 0; i < this -> V ; i++)
            this -> color [i] = 0;
    }

    void addEdge(int start, int end){
        this -> v[start].l.push_back(end);
    }

    int isCycle(int node){
        this -> color[node] = 1;
        list<int> :: iterator  itr;
        for(itr = this -> v[node].l.begin(); itr != this -> v[node].l.end(); ++itr){
            if(this -> color [*itr] == 0 ){
                if(isCycle(*itr))
                    return 1;
            }else if(this -> color [*itr] == 1 ){
                return 1;
            }
        }

        this -> color [node] = 2;
        return 0;
    }

    void bfs(int start){
        queue<int> insq;
        insq.push(start);
        this -> visited[start] = 1;

        while(!insq.empty()){
            int key = insq.front();
            insq.pop();
            cout << key << " ";
            for(auto c : this -> v[key].l){
                if(!this -> visited[c]){
                    insq.push(c);
                    this -> visited[c] = 1;
                }  
            }
        }
        cout << "\n";
    }

    void dfs(int start){
        this -> visited[start] = 1;
        cout << start  << " ";
        for(auto itr = this -> v[start].l.begin(); itr != this -> v[start].l.end(); ++itr){
            if(!visited[*itr])
                dfs(*itr);
        }
    }

    void printgraph(){

        for(int i = 0; i < this -> V; i++){
            cout << i << "-> ";
            for(auto c : this -> v[i].l){
                cout << c << " ";
            }
            cout << endl;
        }

    }
};

int main(){

    int n;
    cout << "Enter the number of vertices in Graph : " << endl;
    cin  >> n;

    srand(time(0));

    Graph g(n);

    // for(int i = 0; i< 20; i++){
    //     int start = rand() % n;
    //     int end = rand() % n;

    //     (*g).addEdge(start, end);

    // }

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.printgraph();

    cout << "\nBFS Algorithm : " << endl;        
    g.make_visited_zero();
    g.bfs(0);

    cout << "DFS Algorithm : " << endl;
    g.make_visited_zero();
    g.dfs(0);

    cout << "\nCheck if cycle present : " << endl;
    g.make_color_white();
    cout << g.isCycle(0) << endl;
    
    return 0;
}
