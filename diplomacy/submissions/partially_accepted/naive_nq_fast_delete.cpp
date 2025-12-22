#include <bits/stdc++.h>
using namespace std;

int cc(int u, vector<int> &vis, vector<set<int>> &con) {
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

    vector<set<int>> con(n);
    priority_queue<tuple<int,int,int>> pq;

    for (int i = 0; i < q; ++i) {
        string op;
        cin >> op;

        if (op == "a") {
            int u, v, p;
            cin >> u >> v >> p;
            u--;
            v--;
            con[u].insert(v);
            con[v].insert(u);
            pq.push({p,u,v});
        } else if (op == "r") {
            int u,v,p;
            tie(p,u,v) = pq.top();
            pq.pop();
            
            con[u].erase(v);
            con[v].erase(u);
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