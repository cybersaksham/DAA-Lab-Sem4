#include<bits/stdc++.h>
using namespace std;

bool compare(vector<int> &a, vector<int> &b){
	if(a[1] == b[1]) return (a[0] < b[0]);
	else return (a[1] < b[1]);
}

int main() {
    freopen("in1.txt", "r", stdin);

	int n;
	cin >> n;

	vector<vector<int>> act(n, vector<int>(3, 0));
	for(int i=0;i<n;i++) {
		cin >> act[i][0];
		cin >> act[i][1];
		cin >> act[i][2];	
	}
	sort(act.begin(), act.end(), compare);

	vector<int> dp(n, 0);
	int res = INT_MIN;

	dp[0] = act[0][2];
	for(int i=1; i<n; i++) {
		dp[i] += act[i][2];
		for(int j=0; j<i; j++) {
			if(act[j][1] <= act[i][0]) {
				dp[i] = max(dp[i], dp[j] + act[i][2]);
				cout << "Activities chosen are : " << i << endl;
			}
		}
		res = max(res, dp[i]);
	}
	
	cout << "Maximum possible value is: " << res << endl;	

	return 0;
}