#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int r, c;
vector<vector<int>> visited;
vector<string> map;
queue<pair<int, int>> swan_q;
queue<pair<int, int>> swan_nq;
queue<pair<int, int>> water_q;
queue<pair<int, int>> water_nq;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool find_BFS() {
    bool found = false;
    int x, y;
    int nx, ny;
    while (!found && !swan_q.empty()) {
        x = swan_q.front().first;
        y = swan_q.front().second;
        swan_q.pop();

        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx < 0 || nx >= r
                || ny < 0 || ny >= c) {
                    continue;
                }
            if (visited[nx][ny] == 1) {
                continue;
            }
            visited[nx][ny] = 1;

            // . X L
            switch (map[nx][ny]) {
                case '.':
                    swan_q.push(make_pair(nx, ny));
                    break;
                case 'X':
                    swan_nq.push(make_pair(nx, ny));
                    break;
                case 'L':
                    found = true;
                    break;
                default:
                    break;
            }
        }
    }

    return found;
}

void water_BFS() {
    int x, y;
    int nx, ny;

    while (!water_q.empty()) {
        x = water_q.front().first;
        y = water_q.front().second;
        water_q.pop();

        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx < 0 || nx >= r
                || ny < 0 || ny >= c) {
                    continue;
                }

            switch (map[nx][ny]) {
                case 'X':
                    water_nq.push(make_pair(nx, ny));
                    map[nx][ny] = '.';
                    break;
                default:
                    break;
            }
        }
    }

}

int main(void) {
    cin >> r >> c;
    
    vector<pair<int, int>> swan;

    string tmp;
    int pos;
    for (int i = 0; i < r; i++) {
        pos = 0;
        cin >> tmp;
        map.push_back(tmp);
        
        while (pos != string::npos) {
            pos = tmp.find('L', pos);
            if (pos != string::npos) {
                swan.push_back(make_pair(i, pos));
                water_q.push(make_pair(i, pos));
                pos++;
            }
        }
        pos = 0;
        while (pos != string::npos) {
            pos = tmp.find('.', pos);
            if (pos != string::npos) {
                water_q.push(make_pair(i, pos));
                pos++;
            }
        }
    }

    visited = vector(r, vector(c, 0));
    
    int cnt = 0;
    int found = false;
    swan_q.push(swan[0]);
    if (swan.size() < 2) {
        cout << "0" << endl;
        return 0;
    }
    visited[swan[0].first][swan[0].second] = 1;
    while (!found) {
        found = find_BFS();
        if (found) break;
        water_BFS();
        water_q = water_nq;
        swan_q = swan_nq;
        while (!water_nq.empty()) water_nq.pop();
        while (!swan_nq.empty()) swan_nq.pop();
        cnt ++;
    }

    cout << cnt << endl;

    return 0;   
}