#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Sorting {
    void merge(int *arr, int low, int mid, int high) {
        int *ans = new int[(high - low + 1) > 0 ? (high - low + 1) : 0];
        int i = low, j = mid + 1, k = 0;

        while(i <= mid && j <= high) {
            if(arr[i] <= arr[j]) ans[k++] = arr[i++];
            else ans[k++] = arr[j++];
        }
        while(i <= mid) ans[k++] = arr[i++];
        while(j <= high) ans[k++] = arr[j++];

        for(int x=0; x<k; x++) arr[x + low] = ans[x];

        delete[] ans;
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

public:
    void print(int const *arr, int low, int high) {
        for(int i=low; i<=high; i++) cout << arr[i] << " ";
        cout << endl;
    }

    void bubbleSort(int *arr, int low, int high) {
        for(int i=high; i>low; i--) {
            int adapt_checker = 0;
            for(int j=low; j<i; j++) {
                if(arr[j + 1] < arr[j]) {
                    int tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    adapt_checker++;
                    this->print(arr, low, high);
                }
            }
            if(adapt_checker == 0) return;
        }
    }

    void insertionSort(int *arr, int low, int high) {
        for(int i=low+1; i<=high; i++) {
            for(int j=i; j>low; j--) {
                if(arr[j - 1] > arr[j]) {
                    int tmp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = tmp;
                    this->print(arr, low, high);
                }
                else break;
            }
        }
    }

    void selectionSort(int *arr, int low, int high) {
        for(int i=low; i<high; i++) {
            int minInd = i, minElem = arr[i];
            for(int j=i+1; j<=high; j++) {
                if(arr[j] < minElem) {
                    minInd = j;
                    minElem = arr[j];
                }
            }
            int tmp = arr[i];
            arr[i] = arr[minInd];
            arr[minInd] = tmp;
            this->print(arr, low, high);
        }
    }

    void mergeSort(int *arr, int low, int high, int fixLow, int fixHigh) {
        if(low >= high) return;
        int mid = low + (high - low) / 2;
        this->mergeSort(arr, low, mid, fixLow, fixHigh);
        this->mergeSort(arr, mid + 1, high, fixLow, fixHigh);
        this->merge(arr, low, mid, high);
        this->print(arr, fixLow, fixHigh);
    }

    void quickSort(int *arr, int low, int high, int fixLow, int fixHigh) {
        if(low >= high) return;
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1, fixLow, fixHigh);
        quickSort(arr, pivot + 1, high, fixLow, fixHigh);
        this->print(arr, fixLow, fixHigh);
    }
};

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

int inputMenu() {
    int menu = 0;
    cout << "Enter 0 for bubble sort." << endl;
    cout << "Enter 1 for insertion sort." << endl;
    cout << "Enter 2 for selection sort." << endl;
    cout << "Enter 3 for merge sort." << endl;
    cout << "Enter 4 for quick sort." << endl;
    cin >> menu;
    return menu;
}

int main() {
    Sorting s1;
    int *arr = inputFromFile("input1.txt");

    int menu = inputMenu();
    while(menu < 0 || menu > 4) {
        cout << "Incorrect Value." << endl;
        menu = inputMenu();
    }

    s1.print(arr, 1, arr[0]);
    switch (menu) {
        case 0:
            s1.bubbleSort(arr, 1, arr[0]);
            break;
        case 1:
            s1.insertionSort(arr, 1, arr[0]);
            break;
        case 2:
            s1.selectionSort(arr, 1, arr[0]);
            break;
        case 3:
            s1.mergeSort(arr, 1, arr[0], 1, arr[0]);
            break;
        case 4:
            s1.quickSort(arr, 1, arr[0], 1, arr[0]);
            break;
        default:
            break;
    }

    delete[] arr;
    return 0;
}