#include <iostream>
#include <queue>

using namespace std;

vector<pair<int, int>> ladder;
int board[101] = {0,};
queue<int> q;
vector<int> visited;
vector<int> cost;


void bfs() {
    int cur;
    int next;
    int found;
    while (!q.empty()) {
        cur = q.front();
        q.pop();

        if (visited[cur] != 0) continue;
        visited[cur] = 1;

        found = false;

        // ladder snake 
        for (int i = 0; i < ladder.size(); i++) {
            if (ladder[i].first == cur) {
                next = ladder[i].second;
                q.push(next);
                if (cost[next] > cost[cur]) {
                    cost[next] = cost[cur];
                }
                found = true;
            }
        }

        if (found) continue;


        for (int i = 1; i <= 6; i++) {
            next = cur + i;
            if (next >= 101) continue;
            if (visited[next] != 0) continue;
            q.push(next);
            if (cost[next] > cost[cur] + 1) {
                cost[next] = cost[cur] + 1;
            }
        }
    }
}

int main(void) {
    int n, m;
    cin >> n >> m;

    int s, e;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        ladder.push_back(make_pair(s, e));
    }

    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        ladder.push_back(make_pair(s, e));
    }

    visited.assign(101, 0);
    cost.assign(101, 101);


    q.push(1);
    cost[1] = 0;
    bfs();

    cout << cost[100] << endl;

    return 0;
}