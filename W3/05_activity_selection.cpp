#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

bool compareInterval(pair<int, int> *p1, pair<int, int> *p2) {
    return p1->second < p2->second;
}

int maxMeetings(pair<int, int> **arr, int n) {
    if(n <= 0) return 0;
    
    sort(arr, arr + n, compareInterval);
    
    int meetings = 1;
    int timeVar = arr[0]->second;
    for(int i=1; i<n; i++) {
        if(arr[i]->first > timeVar) {
            meetings++;
            timeVar = arr[i]->second;
        }
    }
    
    return meetings;
}

int main() {
    int n;
    pair<int, int> **arr;

    ifstream ipFile("05.txt");
    if(ipFile.is_open()) {
        ipFile >> n;

        if(n <= 0) return 0;

        arr = new pair<int, int>*[n];
        for(int i=0; i<n; i++) {
            int a, b;
            ipFile >> a >> b;
            pair<int, int> *it = new pair<int, int>;
            it->first = a;
            it->second = b;
            arr[i] = it;
        }

        ipFile.close();
    }
    else {
        cout << "Input file not present." << endl;
        return 0;
    }

    cout << maxMeetings(arr, n) << endl;

    delete[] arr;

    return 0;
}