#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Santa {
	int idx;
	int x;
	int y;
	int sturn;
	int score;
	bool isOut;
};

struct Cow {
	int x;
	int y;
};

Cow cow;
vector<Santa> vSanta;
int n, m, p, c, d;
int** board;

int edx[8] = {0, 1, 1,  1,  0, -1, -1, -1};
int edy[8] = {1, 1, 0, -1, -1, -1,  0,  1};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = { 0, 1, 0, -1 };


void debugPrintBoard() {

	for (int i = 0; i < n; i++) {
		memset(board[i], 0, n * sizeof(int));
	}

	board[cow.x][cow.y] = 9;
	for (auto& it : vSanta) {
		if (it.isOut) continue;
		board[it.x][it.y] = it.idx;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;

	for (auto& it : vSanta) {
		cout << it.score << " ";
	}
	cout << endl;
}

int getDistance(int xx, int yy, int x, int y) {
	return (x - xx) * (x - xx) + (y - yy) * (y - yy);
}

bool isInBoard(int x, int y) {
	return !(x < 0 || x >= n || y < 0 || y >= n);
}

pair<int, int> getNearSanta() {
	int sX, sY, sDistance = 987654321;
	
	for (auto& santa : vSanta) {
		if (santa.isOut) continue;
		int distance = getDistance(santa.x, santa.y, cow.x, cow.y);
		if (sDistance > distance) {
			sDistance = distance;
			sX = santa.x;
			sY = santa.y;
		}
		else if (sDistance == distance) {
			if (sX < santa.x) {
				sDistance = distance;
				sX = santa.x;
				sY = santa.y;
			}
			else if (sX == santa.x && sY < santa.y) {
				sDistance = distance;
				sX = santa.x;
				sY = santa.y;
			}
		}
	}

	return make_pair(sX, sY);
}

int moveToSanta(pair<int, int>& santa) {
	int sDistance = 987654321;
	int sI = 0;
	for (int i = 0; i < 8; i++) {
		int nx = cow.x + edx[i];
		int ny = cow.y + edy[i];

		if (!isInBoard(nx, ny)) continue;

		int distance = getDistance(santa.first, santa.second, nx, ny);
		if (distance < sDistance) {
			sI = i;
			sDistance = distance;
		}
	}

	cow.x += edx[sI];
	cow.y += edy[sI];

	return sI;
}

bool isSantaHere(int x, int y) {
	bool res = false;
	for (auto& santa : vSanta) {
		if (santa.x == x && santa.y == y) {
			res = true;
			break;
		}
	}

	return res;
}


int moveToCow(Santa& santa) {
	if (santa.isOut) return -1;
	if (santa.sturn > 0) return -1;

	int sDistance = 987654321;
	int sI = 0;
	int curDistance = getDistance(cow.x, cow.y, santa.x, santa.y);

	for (int i = 0; i < 4; i++) {
		int nx = santa.x + dx[i];
		int ny = santa.y + dy[i];

		if (!isInBoard(nx, ny)) continue;

		int distance = getDistance(cow.x, cow.y, nx, ny);

		if (distance < sDistance) {
			if (isSantaHere(nx, ny)) continue;
			sI = i;
			sDistance = distance;
		}
	}

	if (sDistance > curDistance) {
		return -1;
	}

	// move;
	santa.x += dx[sI];
	santa.y += dy[sI];

	if (santa.x == cow.x && santa.y == cow.y) return sI;

	return -1;
}



void erMove(Santa& santa, int x, int y, int dir) {
	//int sX = x + edx[dir];
	//int sY = x + edx[dir];

	if (!isInBoard(x, y)) {
		santa.isOut = true;
		santa.x = -10;
		santa.y = -10;
		return;
	}
	int sX = x + edx[dir];
	int sY = y + edy[dir];
	for (auto& it : vSanta) {
		if (it.isOut) continue;
		if (x == it.x && y == it.y) {
			erMove(it, sX, sY, dir);	
			break;
		}
	}

	santa.x = x;
	santa.y = y;
}

void drMove(Santa& santa, int x, int y, int dir) {
	if (!isInBoard(x, y)) {
		santa.isOut = true;
		santa.x = -10;
		santa.y = -10;
		return;
	}

	int sX = x - dx[dir];
	int sY = y - dy[dir];

	for (auto& it : vSanta) {
		if (it.isOut) continue;
		if (x == it.x && y == it.y) {
			drMove(it, sX, sY, dir);
			break;
		}
	}

	santa.x = x;
	santa.y = y;
}

void hitByCow(int dir) {
	for (auto& santa : vSanta) {
		if (cow.x == santa.x && cow.y == santa.y) {
			santa.score += c;
			santa.sturn = 2;
			int sX = santa.x + edx[dir] * c;
			int sY = santa.y + edy[dir] * c;
			erMove(santa, sX, sY, dir);
			break;
		}
	}
}

void hitBySanta(Santa& santa, int dir) {
	santa.score += d;
	santa.sturn = 2;
	int sX = santa.x - dx[dir] * d;
	int sY = santa.y - dy[dir] * d;
	drMove(santa, sX, sY, dir);
}


void restoreSanta() {
	for (auto& santa : vSanta) {
		if (santa.isOut) continue;
		if (santa.sturn > 0) santa.sturn -= 1;
	}
}

void addSantaScore() {
	for (auto& santa : vSanta) {
		if (santa.isOut) continue;
		santa.score += 1;
	}
}


void moveCow() {
	//cout << "start" << endl;
	//debugPrintBoard();

	restoreSanta();
	pair<int, int> nearSanta = getNearSanta();
	int dir = moveToSanta(nearSanta);
	hitByCow(dir);

	//cout << "cow moved" << endl;
	//debugPrintBoard();

	// snata move
	for (auto& santa : vSanta) {
		dir = moveToCow(santa);
		if (dir < 0) continue;
		hitBySanta(santa, dir);
	}
	
	addSantaScore();
	//cout << "santa moved" << endl;
	//debugPrintBoard();
}


bool isSantaOut() {
	bool res = true;
	for (auto& it : vSanta) {
		if (!it.isOut) {
			res = false;
			break;
		}
	}

	return res;
}

bool compareIdx(Santa const& lhs, Santa const& rhs) {
	return lhs.idx < rhs.idx;
}

void getInput() {
	cin >> n;
	cin >> m;
	cin >> p;
	cin >> c;
	cin >> d;

	int x, y, idx;
	cin >> x;
	cin >> y;

	cow.x = x - 1;
	cow.y = y - 1;

	board = new int* [n];
	for (int i = 0; i < n; i++) {
		board[i] = new int[n] { 0 };
	}


	for (int i = 0; i < p; i++) {
		cin >> idx >> x >> y;
		vSanta.push_back(Santa{ idx, x - 1, y - 1, 0, 0, false });
	}

	std::sort(vSanta.begin(), vSanta.end(), &compareIdx);

	//for (auto& it : vSanta) {
	//	cout << it.idx << endl;
	//}
}

void printScore() {
	for (auto& it : vSanta) {
		cout << it.score << " ";
	}
	cout << endl;
}

void solve() {
	getInput();

	for (int i = 0; i < m; i++) {
		if (isSantaOut()) break;
		moveCow();
	}

	printScore();
}


int main(int argc, char** argv)
{
	solve();

	return 0;
}
