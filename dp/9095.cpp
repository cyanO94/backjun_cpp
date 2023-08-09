#include <vector>
#include <iostream>

using namespace std;
vector<int> dp(12, 0);
int main(void) {
    int n; 
    cin >> n;
    
    
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    //dp.push_back(0);
    //dp.push_back(1); // 1 
    //dp.push_back(2); // 2 1 +1, 2
    //dp.push_back(4); // 3 3, 1 +2 2 + 1 1 + 1 + 1 
    int tmp;
    int target_num;
    for (int i = 0; i < n; i++) {
	cin >> target_num;
		for (int j = 4; j <= target_num; j++) {
       			tmp = dp[j-3];
       			tmp += dp[j-2];
       			tmp += dp[j-1];
       			dp[j] = tmp;
		}
    	cout << dp[target_num] << endl;
    }
    
    
    return 0;
}
