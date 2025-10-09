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

vector<fcmd> make_graph(vector<cmd> g) {
    map<ii,int> edg;
    int q = g.size();
    vector<fcmd> fcmds(g.size());
    int cp = 500000000;
    for(int i = 0; i < q; i++) {
        string c = g[i].c;
        fcmds[i].c = g[i].c;
        if(c == "a") {
            edg[{g[i].u,g[i].v}] = i;
            fcmds[i].u = g[i].u;
            fcmds[i].v = g[i].v;
            fcmds[i].p = -1;
        } else if(c == "r") {
            fcmds[edg[{g[i].u,g[i].v}]].p = cp;
            cp -= rnd.next(100) + 1;
            edg.erase({g[i].u,g[i].v});
        }
    }

    for(auto e: edg) {
        fcmds[e.second].p = cp;
        cp -= rnd.next(100) + 1;
    }

    return fcmds;
}

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

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int q = atoi(argv[2]);
	q -= 1;
    // Set up

    vector<vector<int>> mb;
    set<ii> s;
    mb.push_back(vector<int>());
    for(int i = 0; i < n; i++) {
        mb.back().push_back(i);
        s.insert({i,i});
        if(rnd.next(30) == 0 && i != n-1) {
            mb.push_back(vector<int>());
        }
    }

    vector<cmd> cmds;

    for(auto &v: mb) {
        for(int i = 1; i < (int)v.size(); i++) {
            cmds.push_back({"a",v[rnd.next(i)],v[i]});
            s.insert({cmds.back().u,cmds.back().v});
            s.insert({cmds.back().v,cmds.back().u});
        }
    }
    queue<ii> rms;
    while((int)cmds.size() < q) {
        for(int i = 0; i < 100 && (int)cmds.size() < q; i++) {
            if(rnd.next(10) == 0 && rms.size()) {
                int u,v;
                tie(u,v) = rms.front();
                rms.pop();
                s.erase({u,v});
                s.erase({v,u});
                cmds.push_back({"r",u,v});
            } else if(rnd.next(20) == 0) {
                cmds.push_back({"d",-1,-1});
            } else {
                int u,v;
                do {
                    u = rnd.any(mb[rnd.next(mb.size())]);
                    v = rnd.any(mb[rnd.next(mb.size())]);
                } while(s.count({u,v}));
                s.insert({u,v});
                s.insert({v,u});
                cmds.push_back({"a",u,v});
                if(rnd.next(30) != 0) rms.push({u,v});
            }
        }
        for(int i = 0; i < 100 && (int)cmds.size() < q; i++) {
            if(rnd.next(10) == 0) {
                int u,v;
                do {
                    u = rnd.any(mb[rnd.next(mb.size())]);
                    v = rnd.any(mb[rnd.next(mb.size())]);
                } while(s.count({u,v}));
                s.insert({u,v});
                s.insert({v,u});
                cmds.push_back({"a",u,v});
                if(rnd.next(30) != 0) rms.push({u,v});
            } else if(rnd.next(20) == 0) {
                cmds.push_back({"d",-1,-1});
            } else if (rms.size()) {
                int u,v;
                tie(u,v) = rms.front();
                rms.pop();
                s.erase({u,v});
                s.erase({v,u});
                cmds.push_back({"r",u,v});
            }
        }
    }
    cmds.push_back({"d",-1,-1});
    vector<fcmd> fg = make_graph(cmds);
    fg = permute(fg,n);
    print_test(n,fg);
	return 0;
}
