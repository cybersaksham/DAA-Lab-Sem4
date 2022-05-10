#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
#define maximum 1000

class MST {
    int n;
    int **graph;

public:
    MST(int n, int **graph) {
        this->n = n;
        this->graph = graph;
    }

    void floydWarshall() {
        int ***mat = new int**[2];

        mat[0] = new int*[this->n];
        for(int i=0; i<n; i++) {
            mat[0][i] = new int[n];
            for(int j=0; j<n; j++) {
                if(this->graph[i][j] != maximum && this->graph[i][j] > 0) mat[0][i][j] = this->graph[i][j];
                else {
                    if(i == j) mat[0][i][j] = 0;
                    else mat[0][i][j] = maximum;
                }
            }
        }
        mat[1] = new int*[this->n];
        for(int i=0; i<n; i++) mat[1][i] = new int[n];

        for(int k=1; k<n; k++) {
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    mat[1][i][j] = min(mat[0][i][j], mat[0][i][k] + mat[0][k][j]);
                }
            }
            mat[0] = mat[1];
            mat[1] = new int*[this->n];
            for(int i=0; i<n; i++) mat[1][i] = new int[n];
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) cout << mat[0][i][j] << " ";
            cout << endl;
        }
    }
};

int main() {
    ifstream ipfile("05.txt");


    if(ipfile.is_open()) {
        int n;
        ipfile >> n;

        int **graph = new int*[n];
        for(int i=0; i<n; i++) graph[i] = new int[n];

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) ipfile >> graph[i][j];
        }

        MST mst(n, graph);
        mst.floydWarshall();
    }
    else cout << "Input file not found" << endl;

    return 0;
}