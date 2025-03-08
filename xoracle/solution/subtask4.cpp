#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q; cin >> N >> Q;
	vector<int> group(N, -1);
	vector<vector<int>> q(N, vector<int>(N, -1));
	auto query = [&](int v, int u){
		if (~q[v][u]) return q[v][u];
		cout << "? " << v+1 << ' ' << u+1 << endl;
		int x; cin >> x;
		q[v][u] = q[u][v] = x;
		if (x == -1) {
			exit(0);
		}
		return x;
	};
	int g = 0;
	vector<int> v;
	map<int, int> cnt;
	for (int i = 0; i < N; i++) {
		for (auto j : v) {
			if (query(i, j) == 0) {
				group[i] = group[j];
				break;
			}
		}
		if (group[i] == -1) {
			group[i] = g++;
			v.push_back(i);
		}
		cnt[group[i]]++;
	}
	for (auto i : v) {
		int sm = 0;
		bool flag = 0;
		for (auto j : v) {
			sm += cnt[group[j]] * (query(j, i) ^ 1);
			flag |= query(j, i) == 1;
		}
		if (sm != 2 * N - 2 || flag) continue;
		cout << '!';
		for (auto j : v)
			for (int _ = 0; _ < cnt[group[j]]; _++)
				cout << ' ' << (query(j, i) ^ 1);
		cout << endl;
		break;
	}
}
