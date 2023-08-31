#include <iostream>
#include <queue>
#include <vector>

#define SIZE 100001

using namespace std;

vector<int> visited(SIZE);
queue<pair<int, int>> q;

int bfs(int k) {
    int node;
    int cnt;
    while (!q.empty()) {
        node = q.front().first;
        cnt = q.front().second;
        q.pop();

        if (visited[node] != 0) {
            continue;
        }
        visited[node] = 1;
        //cout << node << endl;

        if (node == k) {
            return cnt;
        }

        if (node > 0) { // node - 1
            if (!visited[node - 1]) q.push(make_pair(node - 1, cnt + 1));
        }

        if (node < SIZE - 1) { // node + 1
            if (!visited[node + 1]) q.push(make_pair(node + 1, cnt + 1));
        }

        if (node * 2 < SIZE) {
            if (!visited[node * 2]) q.push(make_pair(node * 2, cnt + 1));
        }
    }
    
    return 0;
}


int main() {
    int n, k;

    cin >> n >> k;
    
    q.push(make_pair(n, 0));
    int cnt = bfs(k);

    cout << cnt << endl;

    return 0;
}