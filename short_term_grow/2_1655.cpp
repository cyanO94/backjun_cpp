#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
int binary_search(int left, int right, int target) {
	if (right <= left) return left;

	int mid = (right + left) / 2;
	bool a = target > arr[mid];

	if (arr.size() == mid - 1
		&& a) {
			return mid + 1;
	}

	if (a
		&& target < arr[mid + 1]) {
			return mid + 1;
		}
	
	if (a) {
		return binary_search(mid + 1, right, target);
	}
	return binary_search(left, mid, target);
}

int main(void) {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	int tmp;
	int index;
	for (int i = 0; i < n; i++) {
		cin >> tmp;

		// find bi 
		if (arr.size() == 0) {
			index = 0;
		}
		else{
			index = binary_search(0, arr.size(), tmp);
		}
		
		arr.insert(arr.begin() + index, tmp);
/*
		for (int x = 0; x < arr.size(); x++) {
			cout << arr[x] << " ";
		}
		cout << endl;
*/
		cout << arr[(arr.size() -1)/2] << "\n";
	}
	
	return 0;
}
