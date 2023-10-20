#include <iostream>
#include <vector>

using namespace std;

vector<int> factory;

int main() {
	int n;
	cin >> n;
	
	int tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		factory.push_back(tmp);
	}

	long cost = 0;
	for (size_t i = 0; i < factory.size() - 2; i++) {
		if (factory[i] == 0) continue;
		
		while (factory[i] != 0) {	
			if (factory[i + 1] == 0) {
				cost += factory[i] * 3;
				factory[i] = 0;
				continue;
			}

			if (factory[i + 2] != 0 && factory[i + 1] > factory[i + 2]) {
				factory[i] -= 1;
				factory[i+1] -= 1;
				cost += 5;
			}
			else if (factory[i + 2] != 0) {
				factory[i] -= 1;
				factory[i + 1] -= 1;
				factory[i + 2] -= 1;
				cost += 7;
			}
		}
	}
	size_t size = factory.size();
	long minSize = min(factory[size - 2], factory[size - 1]);
	if (minSize != 0) {
		cost += minSize * 5;
		factory[size - 2] -= minSize; 
		factory[size - 1] -= minSize; 
	}

	cost += factory[size - 2] * 3;
	cost += factory[size - 1] * 3;

	cout << cost << endl;	

	return 0;
}
