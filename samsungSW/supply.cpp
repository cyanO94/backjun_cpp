#include<iostream>
#include <queue>
#include <tuple>

using namespace std;

int** board;
int** visited;
int** costBoard;
int n;

struct cmp {
	bool operator()(const tuple<int, int, int>& elem1, const tuple<int, int, int>& elem2) {
		return get<2>(elem1) > get<2>(elem2);
	}
};

priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, cmp> q;

void bfs() {
	q.push(make_tuple(0, 0, 0));
	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };
	int x, y, nx, ny, depth;

	while (!q.empty()) {
		x = get<0>(q.top());
		y = get<1>(q.top());
		depth = get<2>(q.top());
		q.pop();

		if (visited[x][y] != 0) continue;
		visited[x][y] = 1;
		costBoard[x][y] = depth;

		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			q.emplace(nx, ny, costBoard[x][y] + board[nx][ny]);
		}

	}

}

void doFunc() {
	cin >> n;
	
	board = new int* [n];
	visited = new int* [n];
	costBoard = new int* [n];
	for (int i = 0; i < n; i++) {
		board[i] = new int[n];
		visited[i] = new int[n];
		costBoard[i] = new int[n];
	}

	string line;
	for (int i = 0; i < n; i++) {
		cin >> line;
		for (int j = 0; j < n; j++) {
			board[i][j] = line[j] - '0';
			visited[i][j] = 0;
			costBoard[i][j] = 0;
		}
	}

	while (!q.empty()) { q.pop(); }

	bfs();

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << costBoard[i][j] << " ";
	//	}
	//	cout << endl;
	//}

}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	// freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
		doFunc();
		cout << costBoard[n - 1][n - 1] << endl;
	}
	return 0;
}
