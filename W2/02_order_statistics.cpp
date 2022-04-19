#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void swap(int *arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;

    do {
        while(i <= high && arr[i] <= pivot) i++;
        while(j >= low && arr[j] > pivot) j--;
        if(i < j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    } while(i < j);
    arr[low] = arr[j];
    arr[j] = pivot;

    return j;
}

int randomizedPartition(int *arr, int low, int high) {
    int i = rand() % (high - low) + low + 1;
    cout << i << " " << low << " " << high << endl;
    swap(arr, i, low);
    return partition(arr, low, high);
}

int orderStatistics(int *arr, int low, int high, int i) {
    if(low > high) return -1;
    if(low == high) return arr[low];

    int q = randomizedPartition(arr, low, high);
    int k = q - low + 1;
    // cout << q << " " << k << " " << i << endl;

    if(i == k) return arr[q];
    else if(i < k) return orderStatistics(arr, low, q - 1, i);
    else return orderStatistics(arr, q + 1, high, i - k);
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
            if(i > arr[0]) break;
            arr[i++] = a;
        }
        ipFile.close();
    }
    else cout << "Cannot open file " << filename << endl;

    return arr;
}

int main() {
    srand(time(0));
    int *arr = inputFromFile("input2.txt");

    int i;
    cout << "Enter i to find ith order statistics = ";
    cin >> i;

    if(arr[0] >= 1) cout << orderStatistics(arr, 1, arr[0], i) << endl;

    delete[] arr;
    return 0;
}