#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

int findPeak(int const *arr, int low, int high) {
    if(low > high) return 0;
    if(low == high) return arr[low];

    int mid = low + (high - low) / 2;

    int a = INT_MIN, b = INT_MAX, c = INT_MIN;
    if(mid > low) a = arr[mid - 1];
    b = arr[mid];
    if(mid < high) c = arr[mid + 1];

    if(a < b && b < c) return findPeak(arr, mid + 1, high);
    else if(a > b && b > c) return findPeak(arr, low, mid - 1);
    else return arr[mid];
}

int *inputFromFile(string filename) {
    int i = 0;
    int *arr;
    int n;

    string line;
    ifstream ipFile(filename);

    if (ipFile.is_open()) {
        while (getline(ipFile, line)) {
            stringstream str(line);
            int a;
            str >> a;
            if(i == 0) {
                if(a < 1) {
                    arr = new int[1];
                    arr[0] = 0;
                    break;
                }
                arr = new int[a + 1];
            }
            if(i > a) break;
            arr[i++] = a;
        }
        ipFile.close();
    }
    else cout << "Cannot open file " << filename << endl;

    return arr;
}

int main() {
    int *arr = inputFromFile("input2.txt");
    
    cout << findPeak(arr, 1, arr[0]) << endl;

    delete[] arr;
    return 0;
}