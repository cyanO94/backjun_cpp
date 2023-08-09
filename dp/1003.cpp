#include <iostream>
#include <vector>

using namespace std;
vector<int> dp0(41, -1);
vector<int> dp1(41, -1);
int main(void) {
	dp0[0] = 1;
	dp1[0] = 0;
	dp0[1] = 0;
	dp1[1] = 1;
	
	int n;
	cin >> n;
	int fibo;
	for (int i = 0; i < n; i++) {
		cin >> fibo;

		if (dp0[fibo] == -1) {
			for (int j = 2; j <= fibo; j++) {
				dp0[j] = dp0[j - 2] + dp0[j -1];
				dp1[j] = dp1[j - 2] + dp1[j -1];
			}
		}
		cout << dp0[fibo] << " " << dp1[fibo] << endl;
	}
}
