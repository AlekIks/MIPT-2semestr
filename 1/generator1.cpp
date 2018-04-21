#include <iostream>
using namespace std;

int main() {
	freopen ("newgraph.out", "w", stdout);
	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i ++) {
		cout << rand() % n << " " << rand() % n << endl;
	}
	return 0;
}
