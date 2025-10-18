#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define XY_LIMIT 1000000000

struct node {
    ll low, high;
    ll val = 0;
	node *left = nullptr, *right = nullptr;

	node(ll low, ll high)
        : low(low), high(high) {}

    void insert(ll pos, ll val) {
        this->val += val;
        if (low == high) return;

        ll mid = (low + high) / 2;
        if (pos <= mid) {
            if (!left) left = new node(low, mid);
            left->insert(pos, val);
        }
        else {
            if (!right) right = new node(mid+1, high);
            right->insert(pos, val);
        }
    }

    ll sum(ll l, ll h) {
        if (h < low || l > high) return 0;
        if (l <= low && h >= high) return val;

        ll res = 0;
        if (left) res += left->sum(l, h);
        if (right) res += right->sum(l, h);
        return res;
    }
};

struct node2d {
    ll low, high;
    node *tree;
	node2d *left = nullptr, *right = nullptr;

	node2d(ll low, ll high)
        : low(low), high(high), tree(new node(0, XY_LIMIT-1)) {}

    void insert(ll x, ll y, ll val) {
        tree->insert(y, val);
        if (low == high) return;

        ll mid = (low + high) / 2;
        if (x <= mid) {
            if (!left) left = new node2d(low, mid);
            left->insert(x, y, val);
        }
        else {
            if (!right) right = new node2d(mid+1, high);
            right->insert(x, y, val);
        }
    }

    ll sum(ll l, ll r, ll b, ll t) {
        if (r < low || l > high) return 0;
        if (l <= low && r >= high) return tree->sum(b, t);

        ll res = 0;
        if (left) res += left->sum(l, r, b, t);
        if (right) res += right->sum(l, r, b, t);
        return res;
    }
};

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<pair<int, int>> pts;
    node2d *tree = new node2d(0, XY_LIMIT-1);
    for (int i = 0; i < N; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        pts.push_back({x, y});
        tree->insert(x, y, w);
    }

    // check all pairs of points as lower boundaries
    ll result = 0;
    for (int l = 0; l < N; l++) {
        for (int b = 0; b < N; b++) {
            ll value = tree->sum(pts[l].first, min(XY_LIMIT-1, pts[l].first + W - 1),
                                 pts[b].second, min(XY_LIMIT-1, pts[b].second + H - 1));
            result = max(result, value);
        }
    }
    cout << result << endl;
}
