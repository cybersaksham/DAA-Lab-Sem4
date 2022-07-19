#include <bits/stdc++.h>
using namespace std;

int coinSelection(int value, int coinCount, vector<int> const &coins) {
    vector<vector<int>> ans(value + 1);
    for(int i=0; i<=value; i++) {
        vector<int> tmp(coinCount, 0);
        ans[i] = tmp;
    }

    for(int j=0; j<coinCount; j++) ans[0][j] = 1;

    for(int i=1; i<=value; i++) {
        for(int j=0; j<coinCount; j++) {
            int res1 = 0;
            if(i >= coins[j]) res1 = ans[i - coins[j]][j];

            int res2 = 0;
            if(j >= 1) res2 = ans[i][j - 1];

            ans[i][j] = res1 + res2;
        }
    }

    return ans[value][coinCount - 1];
}

int main() {
    freopen("in4.txt", "r", stdin);

    int value, coinCount;
    cin >> value >> coinCount;

    vector<int> coins(coinCount);
    for(int i=0; i<coinCount; i++) cin >> coins[i];

    int ans = coinSelection(value, coinCount, coins);
    cout << "Total no of ways = " << ans << endl;

    return 0;
}