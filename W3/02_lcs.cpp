#include <iostream>
#include <climits>
#include <fstream>
using namespace std;

string lcs(string s, string t) {
    int m = s.size(), n = t.size();
    if(m <= 0 || n <= 0) return 0;

    string **data = new string*[m];
    for(int i=0; i<m; i++) data[i] = new string[n];

    if(s[m - 1] == t[n - 1]) data[m - 1][n - 1] = s[m - 1];
    else data[m - 1][n - 1] = "";

    for(int i=n-2; i>=0; i--) {
        if(s[m - 1] == t[i]) data[m - 1][i] = s[m - 1];
        else data[m - 1][i] = data[m - 1][i + 1];
    }
    for(int i=m-2; i>=0; i--) {
        if(s[i] == t[n - 1]) data[i][n - 1] = t[n - 1];
        else data[i][n - 1] = data[i + 1][n - 1];
    }

    for(int i=m-2; i>=0; i--) {
        for(int j=n-2; j>=0; j--) {
            if(s[i] == t[j]) data[i][j] = s[i] + data[i + 1][j + 1];
            else {
                int a = data[i + 1][j].size();
                int b = data[i][j + 1].size();

                if(a >= b) data[i][j] = data[i + 1][j];
                else data[i][j] = data[i][j + 1];
            }
        }
    }

    string ans = data[0][0];

    for(int i=0; i<m; i++) delete[] data[i];
    delete[] data;

    return ans;
}

int main() {
    string s, t;

    ifstream ipFile("02.txt");
    if(ipFile.is_open()) {
        ipFile >> s >> t;
        ipFile.close();
    }
    else {
        cout << "Input file not present" << endl;
        cout << "Enter 2 strings" << endl;
        cin >> s >> t;
    }

    cout << "Longest common subsequence = " << lcs(s, t) << endl;

    return 0;
}