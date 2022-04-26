#include <iostream>
#include <climits>
#include <fstream>
using namespace std;

int *knapsack(int const *weights, int const *values, int n, int w) {
    if(n <= 0) return 0;
    if(w <= 0) return 0;

    int ***data = new int**[n];
    for(int i=0; i<n; i++) data[i] = new int*[w + 1];

    for(int i=0; i<n; i++) {
        data[i][0] = new int[n + 2];
        data[i][0][0] = 0;
        data[i][0][1] = 0;
    }
    for(int i=1; i<=w; i++) {
        if(weights[n - 1] <= i) {
            int *tmp = new int[n + 1];
            tmp[0] = 1;
            tmp[1] = tmp[2] = values[n - 1];
            data[n - 1][i] = tmp;
        }
        else {
            data[n - 1][i] = new int[n + 1];
            data[n - 1][i][0] = 0;
            data[n - 1][i][1] = 0;
        }
    }

    for(int i=n-2; i>=0; i--) {
        for(int j=1; j<=w; j++) {
            int a = INT_MIN;
            if(weights[i] <= j) a = values[i] + data[i + 1][j - weights[i]][1];
            int b = data[i + 1][j][1];

            int *tmp = new int[n + 1];
            if(a >= b) {
                int *tmp2 = data[i + 1][j - weights[i]];
                tmp[0] = tmp2[0] + 1;
                for(int k=1; k<=(tmp2[0]+1); k++) tmp[k] = tmp2[k];
                tmp[1] += values[i];
                tmp[tmp[0] + 1] = values[i];
            }
            else {
                int *tmp2 = data[i + 1][j];
                tmp[0] = tmp2[0];
                for(int k=1; k<=(tmp2[0]+1); k++) tmp[k] = tmp2[k];
            }
            data[i][j] = tmp;
        }
    }

    int *ans = data[0][w];

    for(int i=0; i<n; i++) delete[] data[i];
    delete[] data;

    return ans;
}

int main() {
    int n, w;
    int *weights;
    int *values;

    ifstream ipFile("03.txt");
    if(ipFile.is_open()) {
        ipFile >> n >> w;

        if(n <= 0) return 0;

        weights = new int[n];
        for(int i=0; i<n; i++) ipFile >> weights[i];
        values = new int[n];
        for(int i=0; i<n; i++) ipFile >> values[i];

        ipFile.close();
    }
    else {
        cout << "Input file not present." << endl;
        return 0;
    }

    int *ans = knapsack(weights, values, n, w);
    cout << "Total Values = " << ans[1] << endl;
    for(int i=1; i<=ans[0]; i++) cout << ans[i+1] << " ";
    cout << endl;

    delete[] weights;
    delete[] values;
    delete[] ans;

    return 0;
}