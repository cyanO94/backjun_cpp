#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> graph;
queue<int> q;
vector<int> visited;

void bfs() {
    int node;
    while (!q.empty()) {
        node = q.front();
        q.pop();

        if (visited[node]) {
            continue;
        }
        visited[node] = 1;

        for (int i = 0; i < graph[node].size(); i++) {
            if (!visited[graph[node][i]]) q.push(graph[node][i]);
        }
    }
}


int main(void) {
    int n, m;
    cin >> n;
    cin >> m;

    int s, e;
    graph.assign(n+1, vector<int>());
    visited.assign(n+1, 0);

    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    q.push(1);
    bfs();

    int cnt = 0;
    for (int i = 1; i < visited.size(); i++) {
        if (visited[i]) cnt += 1;
    }
    cout << cnt - 1 << endl;

    return 0;
}