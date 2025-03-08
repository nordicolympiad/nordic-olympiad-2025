#include <iostream>
#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
#define vii vector<pair<int,int>>
#define ii pair<int,int>
int pp = -1;

struct cmd {
    string c;
    int u,v;
};

struct fcmd {
    string c;
    int u,v,p;
};

vector<fcmd> permute(vector<fcmd> fcmds, int n) {
    vector<int> pm(n);
    iota(pm.begin(),pm.end(),0);
    shuffle(pm.begin(),pm.end());
    for(auto &f : fcmds) {
        if(f.c == "a") {
            f.u = pm[f.u];
            f.v = pm[f.v];
        }
    }
    return fcmds;
}

void print_test(int n, vector<fcmd> fcmds) {
    cout << n << " " << fcmds.size() << endl;
    for(auto &f : fcmds) {
        cout << f.c;
        if(f.c == "a") {
            cout << " " << f.u + 1 << " " << f.v + 1 << " " << f.p;
        }
        cout << endl;
    }
}

int getp(set<int>& ps, bool inc, bool dec) {
	int pd = 0;
	if(inc) {
		if(pp == -1) pp = 1;
		while(ps.count(pp + pd))pd = rnd.next(1000)+1;
        pp += pd;
        ps.insert(pp);
		return pp;
	}
	if(dec) {
		if(pp == -1) pp = 1000000000;
		while(ps.count(pp - pd))pd = rnd.next(1000)+1;
        pp -= pd;
        ps.insert(pp);
		return pp;
	}
	int p = rnd.next(1000000000);
	while(ps.count(p)) p = rnd.next(1000000000);
    ps.insert(p);
	return p;
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int q = atoi(argv[2]);
	bool inc=false,dec=false,line=false;
	int cd = atoi(argv[3]);
	if(atoi(argv[4]) == -1) dec = true;
	if(atoi(argv[4]) == 1) inc = true;
    if(atoi(argv[5]) == 1) line = true;
    set<int> ps;
    vector<fcmd> cmds;
    for(int i = 1; i < n; i++) {
        if((i + 1) % (q/cd) == 0) {
            cmds.push_back({"d",-1,-1,-1});
        } 
        if(line) {
            cmds.push_back({"a",i-1,i,getp(ps,inc,dec)});
        } else {
            cmds.push_back({"a",rnd.next(i),i,getp(ps,inc,dec)});
        }
    }
    while((int)cmds.size() < q-1) {
        if(cmds.size() % (q/cd) == 0) {
            cmds.push_back({"d",-1,-1,-1});
        } else {
            cmds.push_back({"r",-1,-1,-1});
        }
    }
    
    cmds.push_back({"d",-1,-1,-1});
    if (!line) cmds = permute(cmds,n);
    print_test(n,cmds);
	return 0;
}
