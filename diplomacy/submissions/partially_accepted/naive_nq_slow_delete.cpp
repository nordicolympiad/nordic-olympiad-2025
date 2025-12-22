#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Edge {
    int u, v, p;
};


int cc(int u, vector<int> &vis, vector<vector<int>> &con) {
    if (vis[u]) return 0;
    vis[u] = 1;
    int cnt = 1;
    for (int v : con[u]) {
        cnt += cc(v,vis,con);
    }
    return cnt;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> con(n);
    vector<Edge> edgs;

    for (int i = 0; i < q; ++i) {
        string op;
        cin >> op;

        if (op == "a") {
            int u, v, p;
            cin >> u >> v >> p;
            u--;
            v--;
            con[u].push_back(v);
            con[v].push_back(u);
            edgs.push_back({u, v, p});
        } else if (op == "r") {
            int mj = 0;
            int mp = edgs[0].p;
            for (int j = 1; j < (int)edgs.size(); ++j) {
                if (edgs[j].p > mp) {
                    mp = edgs[j].p;
                    mj = j;
                }
            }
            Edge e = edgs[mj];
            edgs.erase(edgs.begin() + mj);
            
            con[e.u].erase(find(con[e.u].begin(),con[e.u].end(),e.v));
            con[e.v].erase(find(con[e.v].begin(),con[e.v].end(),e.u));
        } else if (op == "d") {
            vector<int> vis(n);
            vector<int> ccs;
            for (int j = 0; j < n; ++j) {
                if (!vis[j]) {
                    int size = cc(j, vis, con);
                    ccs.push_back(size);
                }
            }
            sort(ccs.begin(), ccs.end(), greater<int>());
            int ss = 0;
            for (int j = 0; j < (int)ccs.size(); ++j) {
                if (j % 2 == 0) {
                    ss += ccs[j];
                } else {
                    ss -= ccs[j];
                }
            }
            cout << ss << endl;
        }
    }

    return 0;
}