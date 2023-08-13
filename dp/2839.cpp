#include <iostream>
#include <vector>

using namespace std;

vector<int> dp(5001, -1);
int main(int argc, char** argv) {
    int weight;
    cin >> weight;
    
	dp[3] = 1;
	dp[5] = 1;
    for (int i = 3; i <= weight; i++) {
        if (dp[i -3] != -1) {
            dp[i] = dp[i - 3] + 1;
        }
        if (i >= 5 && dp[i-5] != -1) {
            dp[i] = dp[i - 5] + 1;
        }
    }
    
    cout << dp[weight] << endl;

	return 0;
}
