#include<iostream>
#include <vector>

using namespace std;
int* board;
static int SIZE = 10000;

int doFunc() {
	int n; 
	cin >> n;
	vector<int> vIn;

	int tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		vIn.push_back(tmp);
	}
	board = new int[SIZE + 1];
	board[0] = 1;

	for (int i = 1; i <= SIZE; i++) {
		board[i] = 0;
	}
	
	for (int i = 0; i < vIn.size(); i++) {
		for (int j = SIZE; j >= 0; j--) {
			if (board[j] > 0) {
				board[j + vIn[i]] += 1;
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i <= SIZE; i++) {
		if (board[i] > 0) cnt += 1;
	}
	return cnt;

}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
		int cnt = doFunc();
		cout << cnt << endl;
	}
	return 0;
}
