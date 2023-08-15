#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<pair<int, int>> bag;
vector<int> dp(100001, 0);

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}

int main(void) {
	int n, k;
	cin >> n >> k;

	int w, v;
	for (int i = 0; i < n; i++) {
		cin >> w >> v;
		bag.push_back(make_pair(w, v));
	}

	sort(bag.begin(), bag.end(), compare);

	for (int i = 0; i < bag.size(); i++) {
		w = bag[i].first;
		v = bag[i].second;
		for (int j = k-w; j >= 0; j--) {
			if (dp[j + w] < dp[j] + v) {
				dp[j + w] = dp[j] + v;
			}
		}
	}

	cout << dp[k] << endl;
	return 0;
}