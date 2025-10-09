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
	assert(n % 2 == 0);
    // Set up

    vector<vector<int>> mb(2);
    vector<cmd> cmds;
    mb.push_back(vector<int>());
    for(int i = 0; i < n; i+=2) {
        mb[0].push_back(i);
        mb[1].push_back(i + 1);
    }
    priority_queue<tuple<int,int,int>> pq;
    set<ii> e;
    for(int i = 0; i < (q+999)/1000; i++) {
        int u,v;
        do {
            u = rnd.any(mb[0]);
            v = rnd.any(mb[1]);
        } while(e.count({u,v}));
        e.insert({u,v});
        e.insert({v,u});
        cmds.push_back({"a",u,v});
        pq.push({rnd.next(1000000),u,v});
    }
    
    for(auto &v: mb) {
        for(int i = 1; i < (int)v.size(); i++) {
            cmds.push_back({"a",v[rnd.next(i)],v[i]});
        }
    }
    
    while((int)cmds.size() < q) {
        while(pq.size() && (int)cmds.size() < q) {
            int p,u,v;
            tie(p,u,v) = pq.top();
            pq.pop();
            cmds.push_back({"r",u,v});
            e.erase({u,v});
            e.erase({v,u});
        }
        if((int)cmds.size() < q) cmds.push_back({"d",-1,-1});
        while(pq.size() < 5 && (int)cmds.size() < q) {
            int u,v;
            do {
                u = rnd.any(mb[0]);
                v = rnd.any(mb[1]);
            } while(e.count({u,v}));
            e.insert({u,v});
            e.insert({v,u});
            cmds.push_back({"a",u,v});
            pq.push({rnd.next(1000000),u,v});
        }
        if((int)cmds.size() < q) cmds.push_back({"d",-1,-1});
    }
    cmds.push_back({"d",-1,-1});
    vector<fcmd> fg = make_graph(cmds);
    fg = permute(fg,n);
    print_test(n,fg);
	return 0;
}
