#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class MST {
    int n;
    int v;
    int **graph;

    static bool compfunc(int *a1, int *a2) {
        return a1[0] <= a2[0];
    }

public:
    MST(int n, int v, int **graph) {
        this->n = n;
        this->v = v;
        this->graph = graph;
    }

    void bellmanFord(int root) {
        int *dist = new int[this->v];
        for(int i=0; i<v; i++) dist[i] = INT_MAX;
        dist[root] = 0;

        for(int i=1; i<this->v; i++) {
            for(int j=0; j<this->n; j++) {
                int *edge = this->graph[j];
                int wt = edge[0];
                int x = edge[1], y = edge[2];
                if (dist[x] != INT_MAX && dist[x] + wt < dist[y]) {
                    dist[y] = dist[x] + wt;
                }
            }
        }
        for(int i=1; i<this->n; i++) {
            int *edge = this->graph[i];
            int wt = edge[0];
            int x = edge[1], y = edge[2];
            if (dist[x] != INT_MAX && dist[x] + wt < dist[y]) {
                cout << "Negative weight present" << endl;
                return;
            }
        }

        for(int i=0; i<v; i++) cout << i << " " << dist[i] << endl;
    }
};

int main() {
    ifstream ipfile("04.txt");

    if(ipfile.is_open()) {
        int n, v;
        ipfile >> n >> v;

        int **graph = new int*[n];
        for(int i=0; i<n; i++) graph[i] = new int[3];

        for(int i=0; i<n; i++) {
            for(int j=0; j<3; j++) ipfile >> graph[i][j];
        }

        MST mst(n, v, graph);
        mst.bellmanFord(0);
    }
    else cout << "Input file not found" << endl;

    return 0;
}