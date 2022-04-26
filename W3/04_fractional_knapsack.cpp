#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Item{
public:
    int value;
    int weight;

    Item(int a, int b) : value(a), weight(b) {}
};

bool compareFunc(Item *i1, Item *i2) {
    double a = (double)i1->value / (double)i1->weight;
    double b = (double)i2->value / (double)i2->weight;
    return a > b;
}

double fractionalKnapsack(int W, Item **arr, int n) {
    sort(arr, arr + n, compareFunc);
    double count = 0;
    int i = 0;
    while(W > 0) {
        if(i < n) {
            if(arr[i]->weight <= W) {
                cout << "0 " << arr[i]->value << " " << arr[i]->weight << endl;
                count += (double)arr[i]->value;
                W -= arr[i]->weight;
            }
            else {
                cout << "1 " << arr[i]->value << " " << arr[i]->weight << endl;
                count += (double)(W * (double)((double)arr[i]->value / (double)arr[i]->weight));
                W = 0;
                break;
            }
        }
        else break;
        i++;
    }
    return count;
}

int main() {
    int n, w;
    Item **arr;

    ifstream ipFile("04.txt");
    if(ipFile.is_open()) {
        ipFile >> n >> w;

        if(n <= 0) return 0;

        arr = new Item*[n];
        for(int i=0; i<n; i++) {
            int a, b;
            ipFile >> a >> b;
            Item *it = new Item(a, b);
            arr[i] = it;
        }

        ipFile.close();
    }
    else {
        cout << "Input file not present." << endl;
        return 0;
    }

    cout << fractionalKnapsack(w, arr, n) << endl;

    delete[] arr;

    return 0;
}