#include<iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<int, int>> vIn;
int cnt;

pair<int, int> home;
pair<int, int> company;

vector<int> visited;
int minDistance;

int getDistance(int x, int y, int x2, int y2) {
	return abs(x2 - x) + abs(y2 - y);
}


void dfs(int x, int y, int totalDistance, int curCnt) {
	if (curCnt >= cnt) {
		totalDistance += getDistance(x, y, home.first, home.second);
		if (minDistance > totalDistance) {
			minDistance = totalDistance;
		}
		// minDistance = min(minDistance, totalDistance);
		return;
	}
	
	for (int i = 0; i < cnt; i++) {
		if (visited[i] != 0) continue;
		visited[i] = 1;
		dfs(vIn[i].first, vIn[i].second, totalDistance + getDistance(vIn[i].first, vIn[i].second, x, y), curCnt + 1);
		visited[i] = 0;
	}
}

void doFunc() {
	cin >> cnt;

	int x, y;
	cin >> x >> y;
	company = make_pair(x, y);
	cin >> x >> y;
	home = make_pair(x, y);

	for (int i = 0; i < cnt; i++) {
		cin >> x >> y;
		vIn.emplace_back(x, y);
	}

	visited.assign(cnt, 0);
	minDistance = 20000;

	dfs(company.first, company.second, 0, 0);
	vIn.clear();
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
		cout << minDistance << endl;
	}
	return 0;
}
