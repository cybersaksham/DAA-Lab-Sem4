#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
using namespace std;

class MST {
    int n;
    bool *visited;
    int *keys;
    int *parents;
    int **graph;

public:
    MST(int n, int **graph) {
        this->n = n;
        this->graph = graph;
        this->visited = new bool[n];
        for(int i=0; i<n; i++) this->visited[i] = false;
        this->keys = new int[n];
        for(int i=0; i<n; i++) this->keys[i] = INT_MAX;
        this->parents = new int[n];
        for(int i=0; i<n; i++) this->parents[i] = -1;
    }

    void dijkstra(int root) {
        this->visited[root] = false;
        this->keys[root] = 0;

        queue<int> q;
        q.push(root);

        while(!q.empty()) {
            int u = q.front();
            this->visited[u] = true;
            q.pop();

            for(int i=0; i<n; i++) {
                if(this->graph[u][i] > 0 && this->visited[i] == false) {
                    if(this->keys[i] > this->keys[u] + this->graph[u][i]) {
                        this->keys[i] = this->keys[u] + this->graph[u][i];
                        this->parents[i] = u;
                    }
                    q.push(i);
                }
            }
        }
    }

    void printDist() {
        for(int i=0; i<this->n; i++) cout << i << " " << this->keys[i] << endl;
    }
};

int main() {
    ifstream ipfile("01.txt");


    if(ipfile.is_open()) {
        int n;
        ipfile >> n;

        int **graph = new int*[n];
        for(int i=0; i<n; i++) graph[i] = new int[n];

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) ipfile >> graph[i][j];
        }

        MST mst(n, graph);
        mst.dijkstra(0);
        mst.printDist();
    }
    else cout << "Input file not found" << endl;

    return 0;
}