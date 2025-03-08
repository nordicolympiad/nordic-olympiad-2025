#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define XY_LIMIT (1000000000ll)

struct point {
    int x, y, w;

    bool operator<(point o) {
        return x < o.x;
    }
};

struct node {
    ll val, lazy;
};

int power_of_2;
vector<node> seg_tree;

void prop(int id) {
    if (id < power_of_2) {
        seg_tree[2 * id].lazy += seg_tree[id].lazy;
        seg_tree[2 * id + 1].lazy += seg_tree[id].lazy;
    }
    seg_tree[id].val += seg_tree[id].lazy;
    seg_tree[id].lazy = 0;
}

void add_range(int id, int node_low, int node_high, int range_low, int range_high, int val) {
    if (range_high < node_low || range_low > node_high) {
        prop(id);
        return;
    }
    if (range_low <= node_low && range_high >= node_high) {
        seg_tree[id].lazy += val;
        prop(id);
        return;
    }

    prop(id);
    int mid = (node_low + node_high) / 2;
    add_range(2 * id, node_low, mid, range_low, range_high, val);
    add_range(2 * id + 1, mid + 1, node_high, range_low, range_high, val);
    seg_tree[id].val = max(seg_tree[2 * id].val, seg_tree[2 * id + 1].val);
}

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<point> pts(N);
    for (auto &e : pts) {
        int x, y, w;
        cin >> x >> y >> w;
        e = {x, y, w};
    }
    sort(pts.begin(), pts.end());

    // two pointers
    power_of_2 = 1 << (int)ceil(log2(XY_LIMIT + 10));
    seg_tree = vector<node>(2 * power_of_2, {0, 0});
    ll result = 0;
    int r = 0;
    for (int l = 0; l < N; l++) {
        int left_border = pts[l].x;
        int right_border = left_border + W - 1;
        while (r < N && pts[r].x <= right_border) {
            add_range(1, 0, power_of_2 - 1, pts[r].y, pts[r].y + H - 1, pts[r].w);
            r++;
        }
        result = max(result, seg_tree[1].val);
        add_range(1, 0, power_of_2 - 1, pts[l].y, pts[l].y + H - 1, -pts[l].w);
    }
    cout << result << endl;
}
