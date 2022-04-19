#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

long long convertToInt(string a) {
    long long ans;
    stringstream tmp(a);
    tmp >> ans;
    return ans;
}

int equalLength(string &s1, string &s2) {
    int m = s1.size();
    int n = s2.size();

    if(m == n) return m;
    else if(m < n) {
        for(int i=0; i<n-m; i++) s1 = '0' + s1;
        return n;
    }
    else {
        for(int i=0; i<m-n; i++) s2 = '0' + s2;
        return m;
    }
}

string karatsuba(string a, string b) {
    int n = equalLength(a, b);

    if(n == 1) return to_string((a[0] - 48) * (b[0] - 48));

    int x = ceil(n / 2.0);
    int y = n / 2;

    string ah = a.substr(0, x);
    string al = a.substr(x, y);
    string bh = b.substr(0, x);
    string bl = b.substr(x, y);

    string p = karatsuba(ah, bh);
    string q = karatsuba(al, bl);
    string r = karatsuba(to_string(convertToInt(ah) + convertToInt(al)), to_string(convertToInt(bh) + convertToInt(bl)));
    string s = to_string(convertToInt(r) - convertToInt(p) - convertToInt(q));

    return to_string((convertToInt(p) * (long long)pow(10, n)) + (convertToInt(s) * (long long)pow(10, y)) + convertToInt(q));
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << karatsuba(a, b) << endl;

    return 0;
}