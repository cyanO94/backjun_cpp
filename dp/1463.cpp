#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

vector<int> dp(1000001, -1);
int main(int argc, char** argv) {
    int n;
    cin >> n;
    
	int tmp = 0;
	dp[1] = 0;
	dp[2] = 1;
	dp[3] = 1;
    for (int i = 4; i <= n; i++) {
        tmp = INT_MAX;
		if (i % 2 == 0) {
			tmp = dp[i / 2];
		}	
		
		if (i % 3 == 0) {
        	if (dp[i/3] < tmp) tmp = dp[i/3];
		}
		
		if (dp[i-1] < tmp) tmp = tmp = dp[i-1];
    	tmp += 1;

		dp[i] = tmp;
	}
    
    cout << dp[n] << endl;

	return 0;
}
