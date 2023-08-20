#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;
int cnt = 1; 

bool compare(const int a, int b) {
	return a > b;
}

queue<int> q;
void bfs() {
    int node;
    while (!q.empty()) {
        node = q.front();
        q.pop();

        if (visited[node]) {
            continue;
        }
        visited[node] = cnt;
        cnt += 1;

        for (int i = 0; i < graph[node].size(); i++) {
            if (!visited[graph[node][i]]) {
                q.push(graph[node][i]);
            }
        }
    }

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
        sort(graph[i].begin(), graph[i].end()); //, compare);
    }

    q.push(r);
    bfs();

    for (int i = 1; i < visited.size(); i++) {
            cout << visited[i] << "\n";
    }


    return 0;
}