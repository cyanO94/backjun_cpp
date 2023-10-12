#include<iostream>
#include <queue>

using namespace std;

const int n = 16;
int board[n][n];
int visited[n][n];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

pair<int, int> startPoint;
pair<int, int> endPoint;

queue<pair<int, int>> q;

void bfs() {
	int x, y;
	
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();

		if (visited[x][y] != 0) continue;
		visited[x][y] = 1;

		//if (y == endPoint.second && x == endPoint.first) break;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
				continue;
			}

			if (board[nx][ny] != 1) q.emplace(nx, ny);
		}
	}
}

void doFunc() {
	int tmp;
	cin >> tmp;
	while (!q.empty()) q.pop();

	string ttmp;
	for (int i = 0; i < n; i++) {
		cin >> ttmp;
		for (int j = 0; j < ttmp.size(); j++) {
				
			board[i][j] = ttmp[j] - '0';
			visited[i][j] = 0;
			if (ttmp[j] == '2') startPoint = make_pair(i, j);
			else if (ttmp[j] == '3') endPoint = make_pair(i, j);
		}
	}

	q.emplace(startPoint.first, startPoint.second);
	bfs();
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	//cin >> T;
	T = 10;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
		doFunc();
		cout << visited[endPoint.first][endPoint.second] << endl;
	}
	return 0;
}
