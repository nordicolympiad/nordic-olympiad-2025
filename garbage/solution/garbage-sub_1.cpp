#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<pair<int, int>> pts;
    vector<int> weights;
    for (int i = 0; i < N; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        pts.push_back({x, y});
        weights.push_back(w);
    }

    // check all pairs of points as lower boundaries
    ll result = 0;
    for (int l = 0; l < N; l++) {
        for (int b = 0; b < N; b++) {
            ll value = 0;
            for (int i = 0; i < N; i++) {
                if (pts[i].first >= pts[l].first && pts[i].first < pts[l].first + W &&
                    pts[i].second >= pts[b].second && pts[i].second < pts[b].second + H) {
                        value += weights[i];
                }
            }
            result = max(result, value);
        }
    }
    cout << result << endl;
}
