#include<iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int board[4][4];
//int visited[4][4];
set<string> res;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y, string sNum, int curCnt) {
	if (curCnt >= 7) {
		res.insert(sNum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
			continue;
		}
		//if (visited[nx][ny] != 0) {
		//	continue;
		//}
		//visited[nx][ny] = 1;
		dfs(nx, ny, sNum + to_string(board[nx][ny]), curCnt + 1);
		//visited[nx][ny] = 0;
	}
	
}

void doFunc() {
	int tmp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> tmp;
			board[i][j] = tmp;
			//visited[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//visited[i][j] = 1;
			dfs(i, j, to_string(board[i][j]), 1);
			//visited[i][j] = 0;
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
		doFunc();
		cout << res.size() << endl;

		//for(const auto & elem : res) {
		//	cout << elem << endl;
		//}

		res.clear();
	}
	return 0;
}
