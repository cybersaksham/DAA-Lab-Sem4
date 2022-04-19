#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

class Triplet {
public:
    int a, b, c;
    Triplet(int a, int b, int c) : a(a), b(b), c(c) {}
};

Triplet maxCrossingSum(int const *arr, int low, int high) {
    if(low > high) return Triplet(-1, -1, -1);
    if(low == high) return Triplet(low, low, arr[low]);

    int mid = low + (high - low) / 2;

    int leftSum = INT_MIN, leftInd = mid, sum = 0;
    for(int i=mid; i>=low; i--) {
        sum += arr[i];
        if(sum > leftSum) {
            leftSum = sum;
            leftInd = i;
        }
    }

    int rightSum = INT_MIN, rightInd = mid + 1;
    sum = 0;
    for(int i=mid+1; i<=high; i++) {
        sum += arr[i];
        if(sum > rightSum) {
            rightSum = sum;
            rightInd = i;
        }
    }

    return Triplet(leftInd, rightInd, leftSum + rightSum);
}

Triplet maxSumSubarray(int const *arr, int low, int high) {
    if(low > high) return Triplet(-1, -1, -1);
    if(low == high) return Triplet(low, low, arr[low]);

    int mid = low + (high - low) / 2;

    Triplet ans1 = maxSumSubarray(arr, low, mid - 1);
    Triplet ans2 = maxSumSubarray(arr, mid + 1, high);
    Triplet ans3 = maxCrossingSum(arr, low, high);

    if(ans1.c >= ans2.c && ans1.c >= ans3.c) return ans1;
    if(ans2.c >= ans1.c && ans2.c >= ans3.c) return ans2;
    else return ans3;
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
    int *arr = inputFromFile("input2.txt");

    Triplet ans = maxSumSubarray(arr, 1, arr[0]);

    cout << "Max sum subarray is" << endl;
    for(int i=ans.a; i<=ans.b; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Sum = " << ans.c << endl;

    delete[] arr;
    return 0;
}