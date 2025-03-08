#include <iostream>
#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int pp = -1;
int getp(set<int>& ps, bool inc, bool dec) {
	int pd = 0;
	if(inc) {
		if(pp == -1) pp = 1;
		while(ps.count(pp + pd))pd = rnd.next(1000)+1;
		pp += pd;
		return pp;
	}
	if(dec) {
		if(pp == -1) pp = 1000000000;
		while(ps.count(pp - pd))pd = rnd.next(1000)+1;
		pp -= pd;
		return pp;
	}
	int p = rnd.next(1000000000);
	while(ps.count(p)) p = rnd.next(1000000000);
	return p;
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int q = atoi(argv[2]);
	bool inc=false,dec=false;
	int cr = atoi(argv[3]);
	int cd = atoi(argv[4]);
	if(argc > 5 && atoi(argv[5]) == -1) dec = true;
	if(argc > 5 && atoi(argv[5]) == 1) inc = true;
	vector<string> cmds,as(q-cr-cd,"a"),rs(cr,"r"),ds(cd-1,"d");
	cmds.insert(cmds.end(),as.begin(),as.end());
	cmds.insert(cmds.end(),rs.begin(),rs.end());
	cmds.insert(cmds.end(),ds.begin(),ds.end());

	shuffle(cmds.begin(),cmds.end());
	cout << n << " " << q << endl;

	set<tuple<int,int,int>> pcon;
	set<int> ps;
	set<tuple<int,int>> con;
	int attempts = 15;
	for(int i = 0; i < q-1; i++) {
		string c = cmds[i];
		if (c == "a" || (c == "r" && pcon.size() == 0)) {
			int u = rnd.next(n-1) + 1,v = u + 1,p = getp(ps,inc,dec);
			int cc = 0;
			while((u == v || con.count({u,v})) && cc++ <= attempts) u = rnd.next(n-1) + 1,v = u + 1;
			if(cc > attempts) {
				goto emg_del;
			}
			ps.insert(p);
			con.insert({u,v});
			con.insert({v,u});
			pcon.insert({p,u,v});
			cout << "a " << u << " " << v << " " << p << endl;
		} else if(c == "r") {
			emg_del:
			cout << "r" << endl;
			int rp,ru,rv;
			tie(rp,ru,rv) = *pcon.rbegin();
			pcon.erase({rp,ru,rv});
			con.erase({ru,rv});
			con.erase({rv,ru});
		} else {
			cout << "d" << endl;
		}
	}
	cout << "d" << endl;

	return 0;
}
