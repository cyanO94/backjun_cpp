#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<string> map;
queue<pair<int, int>> q;
int n, m;
vector<vector<int>> visited;
vector<vector<int>> cost;

int bfs() {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int x, y, nx, ny;
    int cnt = 0;
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();

        if (visited[x][y] != 0) continue;
        visited[x][y] = 1;

        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            if (visited[nx][ny] != 0) {
                if (cost[nx][ny] + 1 < cost[x][y]) {
                    cost[x][y] = cost[nx][ny] + 1;
                }
            }
            if (visited[nx][ny] == 0 && map[nx][ny] == '1') q.push(make_pair(nx, ny));
        }

        if (x == n -1 && y == m - 1) {
            break;
        }
    }

    return cnt;
}

int main(void) {
    cin >> n >> m;
    string tmp;
    
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        map.push_back(tmp);    
    }

    visited.assign(n, vector<int>(m, 0));
    cost.assign(n, vector<int>(m, 100000));

    q.push(make_pair(0,0));
    cost[0][0] = 1;
    int cnt = bfs();

    cout << cost[n-1][m-1] << endl;


    return 0;    
}