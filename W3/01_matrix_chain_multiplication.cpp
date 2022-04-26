#include <iostream>
#include <climits>
#include <fstream>
using namespace std;

int minOperations(int const *arr, int n) {
    if(n <= 1) return 0;

    int **data = new int*[n + 1];
    for(int i=0; i<=n; i++) data[i] = new int[n + 1];

    for(int i=0; i<=n; i++) {
        for(int j=0; j<=i; j++) data[i][j] = 0;
        if(i < n) data[i][i + 1] = 0;
        if(i < n - 1) data[i][i + 2] = arr[i] * arr[i + 1] * arr[i + 2];
    }

    for(int i=n-3; i>=0; i--) {
        for(int j=i+3; j<=n; j++) {
            int res = INT_MAX;
            for(int k=i+2; k<j; k++) {
                int a = data[i][k];
                int b = data[k][j];
                int c = arr[i] * arr[k] * arr[j];
                res = min(res, a + b + c);
            }
            data[i][j] = res;
        }
    }

    int ans = data[0][n];

    for(int i=0; i<=n; i++) delete[] data[i];
    delete[] data;

    return ans;
}

int main() {
    int n;
    int *dimension;

    ifstream ipFile("01.txt");
    if(ipFile.is_open()) {
        ipFile >> n;
        dimension = new int[n + 1];
        for(int i=0; i<=n; i++) ipFile >> dimension[i];
    }
    else {
        cout << "Input file not present." << endl;
        return 0;
    }

    cout << minOperations(dimension, n) << endl;
    
    delete[] dimension;
    return 0;
}