#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, Q; cin >> N >> Q;
	vector<int> v(N, 0);
	for (int i = 1; i < N; i++) {
		cout << "? 1 " << i+1 << endl;
		cin >> v[i];
	}
	srand(hash<string>()("Asbjørn Lind"));
	while (1) {
		int i = rand() % N;
		for (auto a : {1, 2}) {
			ll sm = 0;
			bool flag = 0;
			for (auto x : v) {
				sm += v[i] ^ x ^ a;
				flag |= !(v[i] ^ x ^ a);
			}
			if (sm != 2 * N - 2 || flag) continue;
			cout << '!';
			for (auto x : v) cout << ' ' << (x ^ v[i] ^ a);
			cout << endl;
			return 0;
		}
	}
}
