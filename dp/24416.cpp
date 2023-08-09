#include <iostream>
#include <vector>

using namespace std;
vector<int> dp(41, -1);
int main(void) {
	dp[1] = 1;
	dp[2] = 1;
	
	int n;
	cin >> n;
	for (int i = 3; i <= n; i++) {
		if (dp[n] == -1) {
			dp[i] = dp[i - 2] + dp[i -1];
		}
	}
	cout << dp[n] << " " << n-2 << endl;
	return 0;
}
