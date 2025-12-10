#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    int add_time, rem_time;
    int p;
    Edge(){}
    Edge(int _u,int _v,int _t,int _p):u(_u),v(_v),add_time(_t),rem_time(_t+1),p(_p){}
};

// value-segtree node provided by you, adapted to handle counts > 1 correctly
struct Node {
    int l, r;
    Node* lc = nullptr;
    Node* rc = nullptr;
    // sum is the alternating sum over values in this interval (largest first)
    // cc is the total count of elements in this interval
    ll sum = 0;
    int cc = 0;

    Node(int l_, int r_) : l(l_), r(r_) {}

    // delta_count: +1 or -1 (or more). idx is the size index (we'll use index==leaf position)
    void pointadd(int idx, int delta_count) {
        if (l == r) {
            cc += delta_count;
            if (cc < 0) cc = 0;  // safety
            sum = (cc & 1) ? l : 0;
            return;
        }

        int mid = (l + r) / 2;
        if (idx <= mid) {
            if (!lc) lc = new Node(l, mid);
            lc->pointadd(idx, delta_count);
        } else {
            if (!rc) rc = new Node(mid + 1, r);
            rc->pointadd(idx, delta_count);
        }
        // recompute sum and cc from children
        sum = 0;
        cc = 0;
        if (rc) { sum += rc->sum; cc += rc->cc; }
        if (lc) {
            cc += lc->cc;
            if (rc && (rc->cc % 2 == 1)) sum -= lc->sum;
            else sum += lc->sum;
        }
    }
};

int N, Q;

// segment-tree over time that stores indices of edges active in that node's interval
vector<vector<int>> segtime;
vector<Edge> edges;
vector<pair<char, array<int,3>>> queries;
vector<ll> answers;

// add edge index to time-segtree node covering [ql,qr)
void seg_add_time(int node, int l, int r, int ql, int qr, int edge_idx) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        segtime[node].push_back(edge_idx);
        return;
    }
    int mid = (l + r) >> 1;
    seg_add_time(node<<1, l, mid, ql, qr, edge_idx);
    seg_add_time(node<<1|1, mid, r, ql, qr, edge_idx);
}

// DSU with rollback; no path compression; unions push ops, rollback pops them
struct DSUOp {
    bool merged;
    int a, b;
    int prev_parent_b;
    int prev_size_a;
};

vector<int> parent_dsu, sz_dsu;
vector<DSUOp> dsu_ops;

// root of value-segtree over sizes 1..N
Node* valroot = nullptr;

// helper to add/remove one component of given size s (s in [1..N])
inline void add_component_size(int s, int delta_count) {
    if (!valroot) valroot = new Node(1, N);
    valroot->pointadd(s, delta_count);
}

// find root without compression
int find_root(int x) {
    while (parent_dsu[x] != x) x = parent_dsu[x];
    return x;
}

void dsu_union(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    DSUOp op;
    op.merged = false;
    if (x == y) {
        dsu_ops.push_back(op);
        return;
    }
    if (sz_dsu[x] < sz_dsu[y]) swap(x,y);
    // prepare op
    op.merged = true;
    op.a = x; op.b = y;
    op.prev_parent_b = parent_dsu[y];
    op.prev_size_a = sz_dsu[x];
    // update value segtree: remove one at size sz[x], remove one at size sz[y], add one at merged size
    add_component_size(sz_dsu[x], -1);
    add_component_size(sz_dsu[y], -1);
    add_component_size(sz_dsu[x] + sz_dsu[y], +1);
    // update DSU
    parent_dsu[y] = x;
    sz_dsu[x] += sz_dsu[y];
    dsu_ops.push_back(op);
}

void dsu_rollback_one() {
    if (dsu_ops.empty()) return;
    DSUOp op = dsu_ops.back(); dsu_ops.pop_back();
    if (!op.merged) return;
    int a = op.a;
    int b = op.b;
    // revert DSU fields
    sz_dsu[a] = op.prev_size_a;
    parent_dsu[b] = op.prev_parent_b;
    // revert value segtree: undo the three updates
    add_component_size(sz_dsu[a] + sz_dsu[b], -1); // remove merged
    add_component_size(sz_dsu[a], +1); // restore a
    add_component_size(sz_dsu[b], +1); // restore b
}

// DFS traverse time-segtree to apply edges active in node's interval and answer queries at leaves
void dfs_time(int node, int l, int r) {
    int before_ops = (int)dsu_ops.size();
    // apply all edges active on this segment
    for (int ei : segtime[node]) {
        dsu_union(edges[ei].u, edges[ei].v);
    }
    if (l + 1 == r) {
        // time point l (1..Q)
        if (l >= 1 && l <= Q && queries[l-1].first == 'd') {
            if (!valroot) answers[l-1] = 0;
            else answers[l-1] = valroot->sum;
        }
    } else {
        int mid = (l + r) >> 1;
        dfs_time(node<<1, l, mid);
        dfs_time(node<<1|1, mid, r);
    }
    // rollback unions applied here
    while ((int)dsu_ops.size() > before_ops) dsu_rollback_one();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> Q;
    queries.resize(Q);
    edges.clear();
    edges.reserve(Q);
    // map pages to edge index, max-heap to pop largest page on 'r'
    priority_queue<pair<int,int>> pq;
    unordered_map<int,int> p_to_e;
    p_to_e.reserve(Q*2);
    vector<int> add_eid_at_query(Q, -1);

    for (int i = 0; i < Q; ++i) {
        char t; cin >> t;
        if (t == 'a') {
            int u,v,p; cin >> u >> v >> p;
            queries[i].first = 'a';
            queries[i].second = {u,v,p};
            edges.emplace_back(u,v,i+1,p);
            int eid = (int)edges.size()-1;
            p_to_e[p] = eid;
            pq.push({p, eid});
            add_eid_at_query[i] = eid;
        } else if (t == 'r') {
            queries[i].first = 'r';
            queries[i].second = {0,0,0};
            if (!pq.empty()) {
                auto top = pq.top(); pq.pop();
                int eid = top.second;
                edges[eid].rem_time = i+1; // active interval [add_time, i+1)
            }
        } else { // d
            queries[i].first = 'd';
            queries[i].second = {0,0,0};
        }
    }
    // remaining edges last until Q+1
    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int eid = top.second;
        edges[eid].rem_time = Q+1;
    }

    // build time segtree: range [1, Q+1)
    int STN = 1;
    while (STN < Q+1) STN <<= 1;
    segtime.assign(STN<<1, {});
    for (int i = 0; i < (int)edges.size(); ++i) {
        int L = edges[i].add_time;
        int R = edges[i].rem_time;
        if (L < R) seg_add_time(1, 1, Q+1, L, R, i);
    }

    // init DSU
    parent_dsu.assign(N+1, 0);
    sz_dsu.assign(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        parent_dsu[i] = i;
        sz_dsu[i] = 1;
    }
    // init value-segtree with N components of size 1
    valroot = new Node(1, N);
    // add N components of size 1 (but we can do single pointadd with delta N)
    valroot->pointadd(1, N);

    answers.assign(Q, -1);

    // run DFS over time
    dfs_time(1, 1, Q+1);

    // output answers
    for (int i = 0; i < Q; ++i) {
        if (queries[i].first == 'd') {
            cout << answers[i] << '\n';
        }
    }
    return 0;
}
