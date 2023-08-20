#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;
int cnt = 1; 

void dfs(int cur) {
    if (visited[cur] != 0) {
        return;
    }

    visited[cur] = cnt;
    cnt += 1;

    for (auto const& item : graph[cur]) {
        dfs(item);
    }
}

bool compare(const int a, int b) {
	return a > b;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);

    int n, m, r;
    cin >> n >> m >> r;
    int s, e;
    graph.assign(n + 1, vector<int>());
    visited = vector(n + 1, 0);

    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    
    for (int i = 0; i < graph.size(); i++) {
        sort(graph[i].begin(), graph[i].end());//, compare);
    }

    dfs(r);

    for (int i = 1; i < visited.size(); i++) {
        if (visited[i] == 0) {
            cout << "0" << "\n";
        }
        else {
            cout << visited[i] << "\n";
        }
        
    }

    return 0;
}