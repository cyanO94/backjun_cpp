#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int*** visited;
int** graph;
int*** cost;

std::queue<tuple<int, int, int>> q;

void showCost(int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << cost[i][j][0] << " ";
        }
        cout << endl;
    }    
    cout << endl;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << cost[i][j][1] << " ";
        }
        cout << endl;
    }    
}

void showVisited(int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << visited[i][j][0] << " ";
        }
        cout << endl;
    }    
    cout << endl;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << visited[i][j][1] << " ";
        }
        cout << endl;
    }    
}

void showGraph(int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }    
    cout << endl;
}


void bfs(int n, int m) {
    int x, y, broken;
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};
    int nx, ny;

    while (!q.empty()) {
        x = get<0>(q.front());
        y = get<1>(q.front());
        broken = get<2>(q.front());
        q.pop();

        if (visited[x][y][broken] != 0) continue;
        visited[x][y][broken] = 1;

        if (x == n && y == m) {
            return;
        }

        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            switch (graph[nx][ny]) {
                case 1:
                    if (broken == 1) {
                        continue;
                    }
                    else {
                        if (visited[nx][ny][1] == 0) {
                            if (cost[nx][ny][1] > cost[x][y][broken] + 1 || cost[nx][ny][broken] == 0) {
                                cost[nx][ny][1] = cost[x][y][broken] + 1;
                            }
                            q.push(make_tuple(nx, ny, 1));
                        }
                    }
                    break;
                case 0:
                    if (visited[nx][ny][broken] == 0) {
                        if (cost[nx][ny][broken] > cost[x][y][broken] + 1 || cost[nx][ny][broken] == 0) {
                            cost[nx][ny][broken] = cost[x][y][broken] + 1;
                        }
                        q.push(make_tuple(nx, ny, broken));
                    }
                    break;
            }
        }
    }


}

int main(void) {
    int n, m;
    cin >> n >> m;

    visited = new int**[n];
    cost = new int**[n];

    for (int i = 0; i < n; i++) {
        visited[i] = new int*[m];
        cost[i] = new int*[m];
        for (int j = 0; j < m; j++) {
            visited[i][j] = new int[2];
            cost[i][j] = new int[2];
        }
    }

    // showVisited(n, m);
    
    string tmp;
    graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[m];
        cin >> tmp;
        for (int k = 0; k < tmp.size(); k++) {
            graph[i][k] = tmp[k] - '0';
        }
    }

    q.push(make_tuple(0, 0, 0));
    cost[0][0][0] = 1;
    bfs(n, m);

    //showVisited(n, m);
    // showCost(n, m);

    if (visited[n-1][m-1][0] == 1 || visited[n-1][m-1][1] == 1) {
        if (cost[n-1][m-1][0] == 0) {
            cout << cost[n-1][m-1][1] << endl;
        }
        else if(cost[n-1][m-1][1] == 0) {
            cout << cost[n-1][m-1][0] << endl;
        }
        else {
            cout << min(cost[n-1][m-1][0], cost[n-1][m-1][1]) << endl;
        }
    }
    else {
        cout << "-1" << endl;
    }

    return 0;
}