#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
using namespace std;

class Tree {
    int val;
    Tree **children;
    int size;

public:
    Tree(int val, int n) {
        this->val = val;
        this->children = new Tree*[n];
        this->size = 0;
    }

    void addChild(Tree *node) {
        this->children[this->size++] = node;
    }

    void print() const {
        queue<Tree const *> q;
        q.push(this);

        while(!q.empty()) {
            Tree const *node = q.front();
            q.pop();

            cout << node->val << ": ";
            for(int i=0; i<node->size; i++) {
                cout << node->children[i]->val << " ";
                q.push(node->children[i]);
            }
            cout << endl;
        }
    }
};

class MST {
    int n;
    bool *visited;
    int *keys;
    int *parents;
    int **graph;

    int minKey(queue<int> q) {
        int minKey = INT_MAX, minInd = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            if(this->keys[u] < minKey) {
                minKey = this->keys[u];
                minInd = u;
            }
        }
        return minInd;
    }

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

    void prims() {
        queue<int> q;
        int root = this->minKey(q);
        this->keys[root] = 0;
        q.push(root);

        while(!q.empty()) {
            int u = this->minKey(q);
            this->visited[u] = true;
            q.pop();

            for(int i=0; i<n; i++) {
                if(this->graph[u][i] > 0 && this->visited[i] == false) {
                    if(this->keys[i] > this->graph[u][i]) {
                        this->keys[i] = this->graph[u][i];
                        this->parents[i] = u;
                    }
                    q.push(i);
                }
            }
        }
    }

    void printTree() const {
        Tree **tree = new Tree*[this->n];
        for(int i=0; i<this->n; i++) tree[i] = NULL;

        Tree *root = NULL;

        int minCost = -1;
        for(int i=0; i<this->n; i++) {
            if(this->parents[i] == -1) {
                root = new Tree(i, this->n);
                tree[i] = root;
            }
            else {
                int p = this->parents[i];
                if(tree[p] == NULL) tree[p] = new Tree(p, this->n);
                if(tree[i] == NULL) tree[i] = new Tree(i, this->n);
                tree[p]->addChild(tree[i]);
                minCost += this->graph[p][i];
            }
        }

        root->print();
        cout << "Minimum cost = " << minCost << endl;
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
        mst.prims();
        mst.printTree();
    }
    else cout << "Input file not found" << endl;

    return 0;
}