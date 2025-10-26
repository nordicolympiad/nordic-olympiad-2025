#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q; cin >> N >> Q;
	vector<int> v(N, 0);
	for (int i = 1; i < N; i++) {
		cout << "? 1 " << i+1 << endl;
		cin >> v[i];
	}
	for (int i = 0; i < N; i++) {
		int sm = 0;
		bool flag = 0;
		for (int j = 0; j < N; j++) {
			sm += v[i] ^ v[j] ^ 1;
			flag |= (v[i] ^ v[j] ^ 1) == 0;
		}
		if (sm != 2 * N - 2 || flag) continue;
		cout << '!';
		for (int j = 0; j < N; j++) cout << ' ' << (v[i] ^ v[j] ^ 1);
		cout << endl;
		break;
	}
}
