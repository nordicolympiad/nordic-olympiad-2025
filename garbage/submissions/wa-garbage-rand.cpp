#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define XY_LIMIT (1000000000ll)

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
    vector<ll> x(N), y(N);
    node2d *tree = new node2d(0, XY_LIMIT-1);
    for (int i = 0; i < N; i++) {
        int w;
        cin >> x[i] >> y[i] >> w;
        tree->insert(x[i], y[i], w);
    }

    // try random pairs
    mt19937 mt(time(0));
    ll result = 0;
    for (int t = 0; t < 200000; t++) {
        ll l = x[mt()%N], b = y[mt()%N];
        ll value = tree->sum(l, min(XY_LIMIT-1, l + W - 1),
                             b, min(XY_LIMIT-1, b + H - 1));
        result = max(result, value);
    }
    cout << result << endl;
}
