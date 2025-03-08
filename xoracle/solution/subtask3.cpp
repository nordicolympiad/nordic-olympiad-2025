#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q; cin >> N >> Q;
	vector<int> group(N, -1);
	vector<vector<int>> q(N, vector<int>(N, -1));
	auto query = [&](int v, int u){
		if (~q[v][u]) return q[v][u];
		cout << "? " << v+1 << ' ' << u+1 << endl;
		cin >> q[v][u];
		if (q[v][u] == -1) {
			exit(0);
		}
		return q[v][u];
	};
	for (int i = 0; i < N; i++) {
		int sm = 0;
		bool flag = 0;
		for (int j = 0; j < N; j++) {
			sm += query(i, j) ^ 1;
			flag |= ((query(i, j) ^ 1) == 0);
		}
		if (sm != 2 * N - 2 || flag) continue;
		cout << '!';
		for (int j = 0; j < N; j++) cout << ' ' << (query(i, j) ^ 1);
		cout << endl;
		break;
	}
}
