#include <bits/stdc++.h>
using namespace std;

int eggDropping(int floors, int eggs) {
    vector<vector<int>> ans(eggs + 1);
    for(int i=0; i<=eggs; i++) {
        vector<int> tmp(floors + 1, 0);
        ans[i] = tmp;
    }

    for(int i=1; i<=eggs; i++) {
        ans[i][0] = 0;
        ans[i][1] = 1;
    }
    for(int j=1; j<=floors; j++) ans[1][j] = j;

    for(int i=2; i<=eggs; i++) {
        for(int j=2; j<=floors; j++) {
            ans[i][j] = INT_MAX;
            for(int k=1; k<=j; k++) {
                ans[i][j] = min(ans[i][j], 1 + max(ans[i-1][k-1], ans[i][j-k]));
            }
        }
    }

    return ans[eggs][floors];
}

int main() {
    freopen("in3.txt", "r", stdin);

    int floors, eggs;
    cin >> floors >> eggs;

    int ans = eggDropping(floors, eggs);
    cout << "Minimum Trials = " << ans << endl;

    return 0;
}