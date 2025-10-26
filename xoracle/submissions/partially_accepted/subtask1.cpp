#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q; cin >> N >> Q;
	vector<int> v(N, 0);
	set<int> z; for (int i = 1; i <= 3; i++) z.insert(i);
	for (int i = 1; i < N; i++) {
		cout << "? 1 " << i+1 << endl;
		cin >> v[i];
		if (z.count(v[i])) z.erase(v[i]);
	}
	int x = 0;
	if (z.size())
		x = *z.begin();
	cout << '!';
	for (auto d : v)
		cout << ' ' << (d ^ x);
	cout << endl;
}
