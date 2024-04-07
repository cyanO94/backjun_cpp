#include <iostream>
#include <queue>
#include <set>

using namespace std;

char board[10][10];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int UP = 0;
int RIGHT = 1;
int DOWN = 2;
int LEFT = 3;

pair<int, int> redPos;
pair<int, int> bluePos;

typedef pair<int, int> pii;

class State {
public:
	int redX;
	int redY;
	int blueX;
	int blueY;
	int cnt;

	bool operator<(const State& other) const {
		if (redX != other.redX) return redX < other.redX;
		if (redY != other.redY) return redY < other.redY;
		if (blueX != other.blueX) return blueX < other.blueX;
		if (blueY != other.blueY) return blueY < other.blueY;
		return cnt < other.cnt;
	}
};

pii roll(int x, int y, int ox, int oy, int dir) {

	int nx = x + dx[dir];
	int ny = y + dy[dir];

	for (int i = 0; i < 9; i++) {
		if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
		
		
		if (board[nx][ny] == 'O') {
			return make_pair(-1, -1);
		}

		if (board[nx][ny] == '#' || (nx == ox && ny == oy)) {
			return make_pair(nx - dx[dir], ny - dy[dir]);
		}

		nx = nx + dx[dir];
		ny = ny + dy[dir];
	}

	return make_pair(x, y);
}


State getNewState(State state, int dir) {
	pii newRedPos, newBluePos;

	if ( (dir == LEFT && state.redY < state.blueY)
		|| (dir == RIGHT && state.redY > state.blueY)
		|| (dir == UP && state.redX < state.blueX)
		|| (dir == DOWN && state.redX > state.blueX)
	) {
		newRedPos = roll(state.redX, state.redY, state.blueX, state.blueY, dir);
		newBluePos = roll(state.blueX, state.blueY, newRedPos.first, newRedPos.second, dir);
	}
	else {
		newBluePos = roll(state.blueX, state.blueY, state.redX, state.redY, dir);
		newRedPos = roll(state.redX, state.redY, newBluePos.first, newBluePos.second, dir);
	}

	State newState = { newRedPos.first, newRedPos.second, newBluePos.first, newBluePos.second, state.cnt + 1 };

	return newState;
}


void do_func() {
	int r, c;
	cin >> r >> c;

	char t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> t;
			board[i][j] = t;

			if (t == 'B') {
				bluePos = make_pair(i, j);
			}
			else if (t == 'R') {
				redPos = make_pair(i, j);
			}
		}
	}

	// 1. 돌리고
	// 2. 구슬 이동 / 구슬 이동
	// 3. 조건 확인(빨강만 탈출)
	// 4. 10 회 이상 -1
	// 먼저 굴릴 구슬 정해야하고

	// set<State> visited;
	queue<State> q;

	State p = { redPos.first, redPos.second, bluePos.first, bluePos.second, 0 };

	q.push(p);
	bool found = false;
	State newState;
	State resState;

	int visited[10][10][10][10] = { 0, };
	visited[p.redX][p.redY][p.blueX][p.blueY] = 1;
	
	while (!q.empty()) {
		State state = q.front();
		q.pop();

		if (state.cnt > 10) break;
		visited[state.redX][state.redY][state.blueX][state.blueY] = 1;

		for (int i = 0; i < 4; i++) {
			newState = getNewState(state, i);

			if (newState.blueX == -1 && newState.blueY == -1) {
				continue;
			}

			if (newState.redX == -1 && newState.redY == -1) {
				found = true;
				resState = newState;
				break;
			}
			if (visited[newState.redX][newState.redY][newState.blueX][newState.blueY] != 0) continue;

			q.push(newState);
		
		}
		
		if (found) break;
	}

	if (!found) {
		cout << "-1" << endl;
	}
	else if (resState.cnt > 10) {
		cout << "-1" << endl;
	}
	else {
		cout << resState.cnt << endl;
	}
}


int main(int argc, char** argv)
{
	// freopen("input.txt", "r", stdin);
	do_func();

	return 0;
}
