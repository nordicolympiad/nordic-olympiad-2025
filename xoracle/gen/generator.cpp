#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int N;

void simple_line() {
	// Simple line from 0 to N-1
	for (int i = 0; i < N-1; i++)
		cout << i << ' ' << i + 1 << '\n';
}

void randomized_line() {
	// A line where the nodes are a random permutation
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	for (int i = 0; i < N-1; i++)
		cout << perm[i] << ' ' << perm[i + 1] << '\n';
}

void maximize_3() {
	// Maximize the number of nodes with degree 3
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	for (int i = 0; i < N; i++) {
		if (i * 2 + 1 < N) cout << perm[i] << ' ' << perm[i * 2 + 1] << '\n';
		if (i * 2 + 2 < N) cout << perm[i] << ' ' << perm[i * 2 + 2] << '\n';
	}
}

void maximize_3_begin() {
	// Maximize the number of nodes with degree 3
	cout << 0 << ' ' << N - 1 << '\n';
	for (int i = 0; i < N - 1; i++) {
		if (i * 2 + 1 < N - 1) cout << i << ' ' << i * 2 + 1 << '\n';
		if (i * 2 + 2 < N - 1) cout << i << ' ' << i * 2 + 2 << '\n';
	}
}

void maximize_3_end() {
	// Maximize the number of nodes with degree 3
	vector<int> perm(N);
	for (int i = 0; i < N; i++) perm[i] = N - i - 1;
	cout << perm[0] << ' ' << perm[N - 1] << '\n';
	for (int i = 0; i < N - 1; i++) {
		if (i * 2 + 1 < N - 1) cout << perm[i] << ' ' << perm[i * 2 + 1] << '\n';
		if (i * 2 + 2 < N - 1) cout << perm[i] << ' ' << perm[i * 2 + 2] << '\n';
	}
}

void maximize_3_mid() {
	// Maximize the number of nodes with degree 3
	vector<int> perm(N);
	for (int i = 0; i < N; i++) perm[i] = (i + N / 2 - 100 + N) % N;
	cout << perm[0] << ' ' << perm[N - 1] << '\n';
	for (int i = 0; i < N - 1; i++) {
		if (i * 2 + 1 < N - 1) cout << perm[i] << ' ' << perm[i * 2 + 1] << '\n';
		if (i * 2 + 2 < N - 1) cout << perm[i] << ' ' << perm[i * 2 + 2] << '\n';
	}
}

void maximize_degrees() {
	// Maximize the number of different degrees
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	cout << perm[0] << ' ' << perm[1] << '\n';
	int k = 0;
	for (int i = 1; i < N; i += k + 1) {
		k++;
		for (int j = i + 1; j < i + k + 1; j++)
			if (j < N)
				cout << perm[i] << ' ' << perm[j] << '\n';
		if (i + k + 1 < N) cout << perm[i] << ' ' << perm[i + k + 1] << '\n';
	}
}

void maximize_degrees_not_random() {
	// Node i from 0 to sqrt(N) has degree i + 3
	cout << 0 << ' ' << N-1 << '\n';
	int j = N-2;
	for (int i = 0; i < j; i++) {
		for (int _ = 0; _ < i + 1; _++)
			if (j > i)
				cout << i << ' ' << j-- << '\n';
		if (i + 1 <= j)
			cout << i << ' ' << i + 1 << '\n';
	}
}

void star() {
	// A star with a random center node
	int center = rnd.next(N);
	for (int i = 0; i < N; i++)
		if (i != center)
			cout << i << ' ' << center << '\n';
}

void star_beg() {
	// A star with a random center node
	int center = 0;
	for (int i = 0; i < N; i++)
		if (i != center)
			cout << i << ' ' << center << '\n';
}

void star_end() {
	// A star with a random center node
	int center = N-1;
	for (int i = 0; i < N; i++)
		if (i != center)
			cout << i << ' ' << center << '\n';
}

void subtask1() {
	// Each node has degree at most 3
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	vector<int> cnt(N, 0);
	set<int> z; z.insert(perm[0]);
	for (int i = 1; i < N; i++) {
		int lb = rnd.next(N);
		auto it = z.lower_bound(lb);
		if (it == z.end()) it--;
		int v = perm[i], u = *it;
		cout << v << ' ' << u << '\n';
		cnt[v] = 1;
		cnt[u]++;
		if (cnt[u] == 3) z.erase(u);
		z.insert(v);
	}
}

void subtask2() {
	// Each node has degree at most 4
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	vector<int> cnt(N, 0);
	set<int> z; z.insert(perm[0]);
	for (int i = 1; i < N; i++) {
		int lb = rnd.next(N);
		auto it = z.lower_bound(lb);
		if (it == z.end()) it--;
		int v = perm[i], u = *it;
		cout << v << ' ' << u << '\n';
		cnt[v] = 1;
		cnt[u]++;
		if (cnt[u] == 4) z.erase(u);
		z.insert(v);
	}
}

void subtask2_not_random() {
	// Each node has degree at most 4
	vector<int> cnt(N, 0);
	set<int> z; z.insert(0);
	for (int i = 1; i < N; i++) {
		int lb = rnd.next(i);
		auto it = z.lower_bound(lb);
		if (it == z.end()) it--;
		int v = i, u = *it;
		cout << v << ' ' << u << '\n';
		cnt[v] = 1;
		cnt[u]++;
		if (cnt[u] == 4) z.erase(u);
		z.insert(v);
	}
}

void tree() {
	// A random tree
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	for (int i = 1; i < N; i++) {
		int j = rnd.next(i);
		cout << perm[i] << ' ' << perm[j] << '\n';
	}
}

void maximize_xor() {
	// Maximize the XOR value of the to nodes with highest degree
	vector<int> perm(N);
	iota(perm.begin(), perm.end(), 0);
	shuffle(perm.begin(), perm.end());
	int sz = 1;
	while (sz * 2 <= N - 1) sz *= 2;
	cout << perm[0] << ' ' << perm[1] << '\n';
	for (int i = 2; i < 2 + sz; i++)
		cout << perm[0] << ' ' << perm[i] << '\n';
	for (int i = 2 + sz; i < N; i++)
		cout << perm[1] << ' ' << perm[i] << '\n';
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	assert (argc >= 5);
	string type = argv[1];
	int subtask = atoi(argv[2]);
	N = atoi(argv[3]);
	cout << subtask << '\n';
	cout << N << ' ';
	if (subtask == 1 || subtask == 2 || subtask == 5 || subtask == 6) cout << N - 1;
	else if (subtask == 3) cout << N * N;
	else if (subtask == 4) cout << 45000;
	cout << '\n';
	if (type == "line") simple_line();
	else if (type == "random_line") randomized_line();
	else if (type == "max3") maximize_3();
	else if (type == "max3beg") maximize_3_begin();
	else if (type == "max3end") maximize_3_end();
	else if (type == "max3mid") maximize_3_mid();
	else if (type == "degrees") maximize_degrees();
	else if (type == "degreesdet") maximize_degrees_not_random();
	else if (type == "star") star();
	else if (type == "star_beg") star_beg();
	else if (type == "star_end") star_end();
	else if (type == "subtask1") subtask1();
	else if (type == "subtask2") subtask2();
	else if (type == "subtask2det") subtask2_not_random();
	else if (type == "general") tree();
	else if (type == "maxor") maximize_xor();
}
