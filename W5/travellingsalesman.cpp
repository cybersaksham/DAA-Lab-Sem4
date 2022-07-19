#include <bits/stdc++.h>
using namespace std;

int travellingSalesmanProblem(vector<vector<int>> graph, int s) {
    int V = graph.size();

    vector<int> vertex;
    for (int i=0; i<V; i++) {
        if (i != s) vertex.push_back(i);
    }
 
    int ans = INT_MAX;
    do {
        int currentWt = 0;
        int k = s;
        for (int i=0; i<vertex.size(); i++) {
            currentWt += graph[k][vertex[i]];
            k = vertex[i];
        }
        currentWt += graph[k][s];
        ans = min(ans, currentWt);
    } while (next_permutation(vertex.begin(), vertex.end()));
 
    return ans;
}

int main() {
    freopen("in2.txt", "r", stdin);

    int V, s;
    cin >> V >> s;
    
    vector<vector<int>> graph(V);
    for(int i=0; i<V; i++) {
        vector<int> tmp(V);
        for(int j=0; j<V; j++) cin >> tmp[j];
        graph[i] = tmp;
    }

    cout << travellingSalesmanProblem(graph, s) << endl;

    return 0;
}