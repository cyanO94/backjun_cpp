#include<iostream>
#include <vector>
#include <queue>

using namespace std;

int target[2];

vector<int> vCP;
vector<vector<int>> vPC;

vector<int> pList1;
vector<int> pList2;

queue<vector<int>> q;

void doFunc() {
	int n, v;
	cin >> n >> v;

	cin >> target[0] >> target[1];
	int p, c;
	vCP.assign(n + 1, 0);
	vPC.assign(n + 1, vector<int>(2, 0));

	for (int i = 0; i < v; i++) {
		cin >> p >> c;
		vCP[c] = p;
		vPC[p].push_back(c);
	}

	int curNode = target[0];
	while (curNode != 1) {
		pList1.push_back(vCP[curNode]);
		curNode = vCP[curNode];
	}
	curNode = target[1];
	while (curNode != 1) {
		pList2.push_back(vCP[curNode]);
		curNode = vCP[curNode];
	}
	int sameParent;
	bool found = false;
	for (int i = 0; i < pList1.size(); i++) {
		for (int j = 0; j < pList2.size(); j++) {
			if (pList1[i] == pList2[j]) {
				sameParent = pList1[i];
				found = true;
				break;
			}
		}
		if (found) break;
	}

	q.push(vPC[sameParent]);
	int cnt = 1;
	vector<int> node;
	while (!q.empty()) {
		int size = q.front().size();
		node = q.front();
		q.pop();

		for (int i = 0; i < size; i++) {
			if (node[i] != 0) {
				q.push(vPC[node[i]]);
				cnt += 1;
			}
			
		}
	}
	pList1.clear();
	pList2.clear();
	cout << sameParent << " " << cnt << endl;
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
	}

	return 0;
}
