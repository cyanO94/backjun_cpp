#include <vector>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

vector<vector<vector<int>>> box;
queue<tuple<int, int, int>> q;
queue<tuple<int, int, int>> nq;
vector<vector<vector<int>>> visited;
int m, n, h;
int visit_cnt = 0;
int empty_cnt = 0;

void bfs() {
    int x, y, z;
    int dx[] = {0, 0, 1, -1, 0, 0};
    int dy[] = {1, -1, 0, 0, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};
    int nx, ny, nz;

    while (!q.empty()) {
        z = get<0>(q.front());
        x = get<1>(q.front());
        y = get<2>(q.front());
        q.pop();

        if (visited[z][x][y] == 1) continue;
        visited[z][x][y] = 1;
        visit_cnt += 1;
        for (int i = 0; i < 6; i++) {
            nx = x + dx[i];
            ny = y + dy[i];
            nz = z + dz[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || nz < 0 || nz >= h) continue;
            if (visited[nz][nx][ny] != 0) continue;
            
            if (box[nz][nx][ny] == 0) {    
                box[nz][nx][ny] = 1;
                nq.push(make_tuple(nz, nx, ny));
            }
        }
    }
}

int main(void) {
    cin >> m >> n >> h;

    int tmp;
    box.assign(h, vector<vector<int>>(n, vector<int>(m, 0)));
    
    for (int k = 0; k < h; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {       
                cin >> tmp;
                box[k][i][j] = tmp;
                if (tmp == 1) {
                    q.push(make_tuple(k, i, j));
                }
                if (tmp == -1) {
                    empty_cnt += 1;
                }
            }
        }
    }
    
    visited.assign(h, vector<vector<int>>(n, vector<int>(m, 0)));
    int cnt = 0;
    int total_visit_cnt = m*n*h - empty_cnt;
    
    while (true) {
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