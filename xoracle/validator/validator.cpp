#include "testlib.h"

using namespace std;

const int MAXN = 100000;
int N, Q;

int parent[MAXN], rnk[MAXN];

int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

bool unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	if (rnk[a] < rnk[b]) swap(a, b);
	parent[b] = a;
	rnk[a] += rnk[b] == rnk[a];
	return true;
}

bool validate_subtask_1(vector<vector<int>> &adj) {
	bool one = false, two = false, three = false;
	for (auto v : adj) {
		one |= v.size() == 1;
		two |= v.size() == 2;
		three |= v.size() == 3;
		if (v.size() > 3) return false;
	}
	return one && two && three;
}

bool validate_subtask_2(vector<vector<int>> &adj) {
	bool one = false, two = false, three = false, four = false;
	for (auto v : adj) {
		one |= v.size() == 1;
		two |= v.size() == 2;
		three |= v.size() == 3;
		four |= v.size() == 4;
		if (v.size() > 4) return false;
	}
	return one + two + three + four >= 3;
}

int main(int argc, char *argv[]) {
	registerValidation();
	int subtask = inf.readInt();
	ensuref(1 <= subtask && subtask <= 6, "subtask is invalid");
	inf.readEoln();

	N = inf.readInt(2, MAXN, "N");
	inf.readSpace();
	Q = inf.readInt(1, MAXN, "Q");
	inf.readEoln();

	if (subtask == 1 || subtask == 2 || subtask == 4 || subtask == 5)
		ensuref(N <= 1000, "N too high");
	else if (subtask == 3)
		ensuref(N <= 300, "N too high");

	if (subtask == 1 || subtask == 2 || subtask == 5 || subtask == 6)
		ensuref(Q == N - 1, "incorrect number of queries");
	else if (subtask == 3)
		ensuref(Q == N * N, "incorrect number of queries");
	else if (subtask == 4)
		ensuref(Q == 45000, "incorrect number of queries");

	for (int i = 0; i < N; i++) parent[i] = i, rnk[i] = 0;

	vector<vector<int>> adj(N);
	for (int _ = 1; _ < N; _++) {
		int v = inf.readInt(0, N-1, "v");
		inf.readSpace();
		int u = inf.readInt(0, N-1, "u");
		inf.readEoln();
		ensuref(v != u, "no self loops");
		ensuref(unite(v, u), "loop in tree detected");
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	inf.readEof();

	if (subtask == 1)
		ensuref(validate_subtask_1(adj), "Subtask one guarantee not upheld");
	if (subtask == 2)
		ensuref(validate_subtask_2(adj), "Subtask two guarantee not upheld");

	return 0;
}
