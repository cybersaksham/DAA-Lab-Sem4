#include <iostream>
#include <fstream>
using namespace std;

int **initMat(int n) {
    int **arr = new int*[n + 1];
    arr[0] = new int[1];
    arr[0][0] = n;

    for(int i = 1; i <= n; i++) arr[i] = new int[n];

    return arr;
}

void deleteMat(int **matrix) {
    int n = matrix[0][0];
    for(int i=0; i<=n; i++) delete[] matrix[i];
    delete[] matrix;
}

void printMat(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << matrix[i+1][j] << " ";
        cout << endl;
    }
}

int **add(int **matrix1, int **matrix2, int n) {
    int **temp = initMat(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) temp[i][j] = matrix1[i][j] + matrix2[i][j];
    }
    return temp;
}

int **subtract(int **matrix1, int **matrix2, int n) {
    int **temp = initMat(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) temp[i][j] = matrix1[i][j] - matrix2[i][j];
    }
    return temp;
}

int **strassenMultiply(int **A, int **B, int n) {
    if (n == 1) {
        int **res = initMat(1);
        res[1][0] = A[1][0] * B[1][0];
        return res;
    }

    int **res = initMat(n);
    int k = n / 2;

    int **A11 = initMat(k);
    int **A12 = initMat(k);
    int **A21 = initMat(k);
    int **A22 = initMat(k);
    int **B11 = initMat(k);
    int **B12 = initMat(k);
    int **B21 = initMat(k);
    int **B22 = initMat(k);

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][k + j];
            A21[i][j] = A[k + i][j];
            A22[i][j] = A[k + i][k + j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][k + j];
            B21[i][j] = B[k + i][j];
            B22[i][j] = B[k + i][k + j];
        }
    }

    int **P1 = strassenMultiply(A11, subtract(B12, B22, k), k);
    int **P2 = strassenMultiply(add(A11, A12, k), B22, k);
    int **P3 = strassenMultiply(add(A21, A22, k), B11, k);
    int **P4 = strassenMultiply(A22, subtract(B21, B11, k), k);
    int **P5 = strassenMultiply(add(A11, A22, k), add(B11, B22, k), k);
    int **P6 = strassenMultiply(subtract(A12, A22, k), add(B21, B22, k), k);
    int **P7 = strassenMultiply(subtract(A11, A21, k), add(B11, B12, k), k);

    int **C11 = subtract(add(add(P5, P4, k), P6, k), P2, k);
    int **C12 = add(P1, P2, k);
    int **C21 = add(P3, P4, k);
    int **C22 = subtract(subtract(add(P5, P1, k), P3, k), P7, k);

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < k; j++) {
            res[i][j] = C11[i][j];
            res[i][j + k] = C12[i][j];
            res[k + i][j] = C21[i][j];
            res[k + i][k + j] = C22[i][j];
        }
    }

    deleteMat(P1);
    deleteMat(P2);
    deleteMat(P3);
    deleteMat(P4);
    deleteMat(P5);
    deleteMat(P6);
    deleteMat(P7);
    deleteMat(C11);
    deleteMat(C12);
    deleteMat(C21);
    deleteMat(C22);
    deleteMat(A11);
    deleteMat(A12);
    deleteMat(A21);
    deleteMat(A22);
    deleteMat(B11);
    deleteMat(B12);
    deleteMat(B21);
    deleteMat(B22);

    return res;
}

int ***matrixInput(string filename) {
    ifstream ipFile(filename);

    int **matrix1;
    int **matrix2;
    int m;

    if (ipFile.is_open()) {
        ipFile >> m;
        matrix1 = new int*[m + 1];
        matrix2 = new int*[m + 1];

        matrix1[0] = new int[1];
        matrix1[0][0] = m;
        matrix2[0] = new int[1];
        matrix2[0][0] = m;

        for(int i=1; i<=m; i++) {
            matrix1[i] = new int[m];
            for(int j=0; j<m; j++) ipFile >> matrix1[i][j];
        }
        for(int i=1; i<=m; i++) {
            matrix2[i] = new int[m];
            for(int j=0; j<m; j++) ipFile >> matrix2[i][j];
        }

        ipFile.close();
    }
    else cout << "Cannot open file " << filename << endl;

    int ***res = new int**[2];
    res[0] = matrix1;
    res[1] = matrix2;

    return res;
}

int main() {
    int ***res = matrixInput("inputMat.txt");
    int **matrix1 = res[0];
    int **matrix2 = res[1];

    cout << "Matrix A" << endl;
    printMat(matrix1, matrix1[0][0]);
    cout << "Matrix B" << endl;
    printMat(matrix2, matrix2[0][0]);

    cout << "Result" << endl;
    int **ans = strassenMultiply(matrix1, matrix2, matrix1[0][0]);
    printMat(ans, ans[0][0]);

    deleteMat(ans);
    deleteMat(matrix1);
    deleteMat(matrix2);
    delete[] res;

    return 0;
}