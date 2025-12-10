#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, Q; cin >> N >> Q;
	vector<int> cnt(N+1, 0);
	cnt[0] = 1;
	for (int i = 1; i < N; i++) {
		cout << "? 1 " << i+1 << endl;
		int x; cin >> x;
		cnt[x]++;
	}
	int mx = 0, sec = 1;
	if (cnt[0] < cnt[1]) swap(mx, sec);
	for (int i = 2; i < N+1; i++) {
		if (cnt[i] > cnt[mx]) {
			sec = mx;
			mx = i;
		}
		else if (cnt[i] > cnt[sec]) sec = i;
	}

	int num_sols = 0;
	for (auto x : {mx, sec}) {
		int sm = 0;
		bool flag = 0;
		for (int i = 0; i < N+1; i++) {
			sm += cnt[i] * (i ^ x ^ 1);
			flag |= cnt[i] > 0 && !(i ^ x ^ 1);
		}
		if (sm != 2 * N - 2 || flag) continue;
		num_sols++;
	}

	assert(num_sols == 1);

	for (auto x : {mx, sec}) {
		int sm = 0;
		bool flag = 0;
		for (int i = 0; i < N+1; i++) {
			sm += cnt[i] * (i ^ x ^ 1);
			flag |= cnt[i] > 0 && !(i ^ x ^ 1);
		}
		if (sm != 2 * N - 2 || flag) continue;
		cout << '!';
		for (int i = 0; i < N+1; i++)
			while(cnt[i]--)
				cout << ' ' << (i ^ x ^ 1);
		cout << endl;
		break;
	}
}
