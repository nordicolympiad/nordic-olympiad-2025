#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main(int argc, char **argv) {
    init_io(argc, argv);

    int subtask;
    judge_in >> subtask;

    int N,Q;
    judge_in >> N >> Q;

    vi degrees(N);
    rep(i,0,N-1)
    {
        int u,v;
        judge_in >> u >> v;
        degrees[u]++;
        degrees[v]++;
    }
    cout << N << " " << Q << endl;

	int qcount = 0;
	for (;;) {
    	char qtype;
		if (!(cin >> qtype)) wrong_answer("EOF1");

		if (qtype == '?') {
            int u,v;
            if (!(cin >> u >> v)) wrong_answer("EOF2");
            if (u < 1 || u > N || v < 1 || v > N) wrong_answer("Out of bounds query");
            u--; v--;
            qcount++;
            if (qcount > Q) {
                wrong_answer("Too many queries");
            }
            int ans = degrees[u] ^ degrees[v];
            cout << ans << endl;
		} else if (qtype == '!') {
			break;
		} else {
			wrong_answer("Invalid query type %c", qtype);
		}
	}

    vector<int> ans(N);
    for (int& d : ans) {
        if (!(cin >> d)) wrong_answer("EOF3");
    }
    sort(all(ans));
    sort(all(degrees));

    if (ans != degrees) {
        wrong_answer("found wrong set of degrees");
    }

	string trailing;
	if (cin >> trailing){
		wrong_answer("Trailing output");
	}

    accept();
}
