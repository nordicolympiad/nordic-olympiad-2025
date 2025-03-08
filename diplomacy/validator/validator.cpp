#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;
const int MAXQ = 500000;
const int MAXP = 1000000000;

int main() {
	registerValidation();
	set<tuple<int,int>> con;
	set<tuple<int,int,int>> pcon;
	set<int> ps;

	int n = inf.readInt(1, MAXN, "n");
	inf.readSpace();
	int q = inf.readInt(1, MAXQ, "q");
	inf.readEoln();
	for(int i = 0; i < q; i++) {
		string c = inf.readWord("[ard]","c");
		if(c == "a") {
			inf.readSpace();
			int u = inf.readInt(1,n,"u");
			inf.readSpace();
			int v = inf.readInt(1,n,"v");
			if(u == v) {
				quit(_wa,"u=v");
			}
			inf.readSpace();
			int p = inf.readInt(1,MAXP,"p");
			if(ps.count(p)) {
				quit(_wa, "Duplicate P");
			}
			if(con.count({u,v}) || con.count({v,u})) {
				quit(_wa, "Inserting existing edge");
			}
			ps.insert(p);
			con.insert({u,v});
			con.insert({v,u});
			pcon.insert({p,u,v});
		} else if(c == "r") {
			if(pcon.size() == 0) {
				quit(_wa, "Deleting when no edge exists");
			}
			int rp,ru,rv;
			tie(rp,ru,rv) = *pcon.rbegin();
			pcon.erase({rp,ru,rv});
			con.erase({ru,rv});
			con.erase({rv,ru});
		}
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
