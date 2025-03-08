#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    int x, y, w;

    bool operator<(point o) {
        return x < o.x;
    }
};

struct node {
    ll low, high;
    ll val = 0, laz = 0;
	node *left = nullptr, *right = nullptr;

	node(ll low, ll high)
        : low(low), high(high) {}

    void insert(ll pos) {
        if (low == high) return;

        ll mid = (low + high) / 2;
        if (pos <= mid) {
            if (!left) left = new node(low, mid);
            left->insert(pos);
        }
        else {
            if (!right) right = new node(mid+1, high);
            right->insert(pos);
        }
    }

    void prop() {
        if (left) left->laz += laz;
        if (right) right->laz += laz;
        val += laz;
        laz = 0;
    }
	
    void recalc() {
        if (!left && !right) return;
        val = -(1ll << 62ll);
        if (left) val = max(val, left->val);
        if (right) val = max(val, right->val);
    }

    void add_range(ll l, ll h, ll val) {
        if (h < low || l > high) {
            prop();
            return;
        }
        if (l <= low && h >= high) {
            laz += val;
            prop();
            return;
        }

        prop();
        if (left) left->add_range(l, h, val);
        if (right) right->add_range(l, h, val);
        recalc();
    }
};

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<point> pts(N);
    node *seg_tree = new node(0, 1000000000 + H);
    for (auto &e : pts) {
        int x, y, w;
        cin >> x >> y >> w;
        e = {x, y, w};
        seg_tree->insert(y);
        seg_tree->insert(y + H - 1);
    }
    sort(pts.begin(), pts.end());

    // two pointers
    int r = 0;
    ll result = 0;
    for (int l = 0; l < N; l++) {
        int left_border = pts[l].x;
        int right_border = left_border + W - 1;
        while (r < N && pts[r].x <= right_border) {
            seg_tree->add_range(pts[r].y, pts[r].y + H - 1, pts[r].w);
            r++;
        }
        result = max(result, seg_tree->val);
        seg_tree->add_range(pts[l].y, pts[l].y + H - 1, -pts[l].w);
    }
    cout << result << endl;
}
