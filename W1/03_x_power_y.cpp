#include <iostream>
using namespace std;

double calcPower(int x, int y) {
    if(x == 0) return 0.0;
    if(y < 0) return 1.0 / calcPower(x, -1 * y);
    if(y == 0) return 1.0;
    if(y == 1) return (double)x;

    double tmp = calcPower(x, y / 2);
    if(y % 2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << calcPower(x, y) << endl;

    return 0;
}