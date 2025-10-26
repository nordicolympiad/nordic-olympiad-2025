#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q; cin >> N >> Q;
	bool a = 1, b = 1, c = 1, d = 1;
	vector<int> v(N, 0);
	for (int i = 1; i < N; i++) {
		cout << "? 1 " << i+1 << endl;
		cin >> v[i];
		if (v[i] == 1) a = 0, d = 0;
		if (v[i] == 2) b = 0, d = 0;
		if (v[i] == 3) c = 0, d = 0;
		if (v[i] == 5) b = 0, c = 0;
		if (v[i] == 6) a = 0, c = 0;
		if (v[i] == 7) a = 0, b = 0;
	}
	int x = 0;
	if (a) x = 1;
	if (b) x = 2;
	if (c) x = 3;
	if (d) x = 4;
	cout << '!';
	for (auto d : v) cout << ' ' << (d ^ x);
	cout << endl;
}
