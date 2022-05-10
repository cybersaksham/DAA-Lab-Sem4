#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

class DisjointSet {
    int *parent;
    int n;

public:
    DisjointSet(int n) {
        this->n = n;
        this->parent = new int[n];
        for(int i=0; i<n; i++) this->parent[i] = -1;
    }

    int find(int i) const {
        if(this->parent[i] == -1) return i;
        return this->find(this->parent[i]);
    }

    void unite(int x, int y) {
        int p1 = this->find(x), p2 = this->find(y);
        if(p1 != p2) {
            this->parent[p1] = p2;
        }
    }
};

class MST {
    int n;
    int **graph;

    static bool compfunc(int *a1, int *a2) {
        return a1[0] <= a2[0];
    }

public:
    MST(int n, int **graph) {
        this->n = n;
        this->graph = graph;
    }
    
    void kruskal() {
        sort(this->graph, this->graph + n, this->compfunc);

        DisjointSet ds(2 * this->n);
        int minCost = 0;
        for(int i=0; i<n; i++) {
            int *edge = graph[i];
            int wt = edge[0];
            int x = edge[1], y = edge[2];
            cout << x << " + " << y << " = " << wt << endl;
        }

        cout << "Edges in MST:" << endl;
        for(int i=0; i<n; i++) {
            int *edge = graph[i];
            int wt = edge[0];
            int x = edge[1], y = edge[2];

            if(ds.find(x) != ds.find(y)) {
                ds.unite(x, y);
                minCost += wt;
                cout << x << " + " << y << " = " << wt << endl;
            }
        }

        cout << "Minimum cost = " << minCost << endl;
    }
};

int main() {
    ifstream ipfile("02.txt");


    if(ipfile.is_open()) {
        int n;
        ipfile >> n;

        int **graph = new int*[n];
        for(int i=0; i<n; i++) graph[i] = new int[3];

        for(int i=0; i<n; i++) {
            for(int j=0; j<3; j++) ipfile >> graph[i][j];
        }

        MST mst(n, graph);
        mst.kruskal();
    }
    else cout << "Input file not found" << endl;

    return 0;
}