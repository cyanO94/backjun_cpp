#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<vector<int>> box;
queue<pair<int, int>> q;
queue<pair<int, int>> nq;
vector<vector<int>> visited;
int m, n;
int visit_cnt = 0;
int empty_cnt = 0;
void bfs() {
    int x, y;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int nx, ny;

    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();

        if (visited[x][y] == 1) continue;
        visited[x][y] = 1;
        visit_cnt += 1;
        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (visited[nx][ny] != 0) continue;
            
            if (box[nx][ny] == 0) {    
                box[nx][ny] = 1;
                nq.push(make_pair(nx, ny));
            }
        }
    }
}

bool check_box() { // timeout
    bool found = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (box[i][j] == 0) {
                found = false;
            }
        }
    }

    return found;
}

int main(void) {
    cin >> m >> n;

    int tmp;
    box.assign(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tmp;
            box[i][j] = tmp;
            if (tmp == 1) {
                q.push(make_pair(i, j));
            }
            if (tmp == -1) {
                empty_cnt += 1;
            }
        }
    }
    visited.assign(n, vector<int>(m, 0));
    int cnt = 0;
    int total_visit_cnt = m*n - empty_cnt;
    while (true) {
        //if (check_box()) {
        bfs();
        if (visit_cnt >= total_visit_cnt) {
            break;
        }
        cnt += 1;
        
        if (nq.empty()) {
            cnt = -1;
            break;
        }

        q = nq;
        while (!nq.empty()) nq.pop();
    }

    cout << cnt << "\n";
    return 0;
}