#include<iostream>
#include <string>
#include <queue>

using namespace std;

char** board;

pair<int, int> direction;

int UP = 0;
int DOWN = 1;
int RIGHT = 2;
int LEFT = 3;

pair<int, int> directionList[4] = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, 1),make_pair(0, -1) };

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

struct param2 {
	int x;
	int y;
	int memory;
	int direction;

	param2(int x, int y, int memory, int direction) : x(x), y(y), memory(memory), direction(direction) {};
};

queue<param2> q;
int row, col;
int**** visited;
bool canEnd;

void bfs() {
	int x, y, memory;
	int direction;
	int nx, ny;

	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		memory = q.front().memory;
		direction = q.front().direction;
		q.pop();

		if (visited[x][y][direction][memory] != 0) continue;
		visited[x][y][direction][memory] = 1;

		if (board[x][y] == '@') {
			canEnd = true;
			break;
		}
		bool qFlag = false;
		if (board[x][y] - '0' >= 0 && board[x][y] - '0' <= 9) {
			memory = board[x][y] - '0';
		}
		else {
			switch (board[x][y]) {
			case '<':
				direction = LEFT;
				break;
			case '>':
				direction = RIGHT;
				break;
			case 'v':
				direction = DOWN;
				break;
			case '^':
				direction = UP;
				break;
			case '_':
				if (memory == 0) direction = RIGHT;
				else direction = LEFT;
				break;
			case '|':
				if (memory == 0) direction = DOWN;
				else direction = UP;
				break;
			case '?':	// 
				qFlag = true;
				break;
			case '.':
				break;
			case '+':
				if (memory == 15) memory = 0;
				else memory += 1;
				break;
			case '-':
				if (memory == 0) memory = 15;
				else memory -= 1;
				break;
			}
		}
		if (qFlag) {
			for (int i = 0; i < 4; i++) {
				nx = (x + directionList[i].first);
				ny = (y + directionList[i].second);
				if (nx < 0) nx = row - 1;
				else if (nx >= row) nx = 0;
				if (ny < 0) ny = col - 1;
				else if (ny >= col) ny = 0;

				if (visited[nx][ny][i][memory] == 0) q.push(param2(nx, ny, memory, i));
			}
		}
		else
		{
			nx = (x + directionList[direction].first);
			ny = (y + directionList[direction].second);
			if (nx < 0) nx = row - 1;
			else if (nx >= row) nx = 0;
			if (ny < 0) ny = col - 1;
			else if (ny >= col) ny = 0;
			if (visited[nx][ny][direction][memory] == 0) q.push(param2(nx, ny, memory, direction));

		}
	}
}

void doFunc() {
	cin >> row >> col;
	
	board = new char* [row];
	visited = new int*** [row];

	int cnt = 0;
	string tmp;

	for (int i = 0; i < row; i++) {
		cin >> tmp;
		board[i] = new char[col];
		visited[i] = new int** [col];
		for (int j = 0; j < col; j++) {
			board[i][j] = tmp[j];
			visited[i][j] = new int*[4];
			for (int k = 0; k < 4; k++) {
				visited[i][j][k] = new int[16]();
			}

			if (tmp[j] == '@') {
				cnt += 1;
			}
		}
	}
	
	if (cnt == 0) return;
	canEnd = false;
	q.push(param2(0,0,0, RIGHT));
	bfs();
	while (!q.empty()) q.pop();
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
		if (canEnd)
		{
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		canEnd = false;

	}

	return 0;
}
