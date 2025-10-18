#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<pair<int, int>> pts(N); // <x-position, weight>
    for (auto &e : pts) {
        int x, y, w;
        cin >> x >> y >> w;
        e = {x, w};
    }
    sort(pts.begin(), pts.end());

    // two pointers
    int r = 0;
    ll result = 0, running_weight = 0;
    for (int l = 0; l < N; l++) {
        int left_border = pts[l].first;
        int right_border = left_border + W - 1;
        while (r < N && pts[r].first <= right_border) {
            running_weight += pts[r].second;
            r++;
        }
        result = max(result, running_weight);
        running_weight -= pts[l].second;
    }
    cout << result << endl;
}
