#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define N_LIMIT 2000

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    vector<pair<int, int>> pts;
    vector<int> weights;
    set<int> coords_x, coords_y;
    for (int i = 0; i < N; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        pts.push_back({x, y});
        weights.push_back(w);
        coords_x.insert(x);
        coords_x.insert(x + W);
        coords_y.insert(y);
        coords_y.insert(y + H);
    }

    // coordinate compression
    map<int, int> compress_x, compress_y;
    for (auto &e : coords_x) compress_x[e] = compress_x.size();
    for (auto &e : coords_y) compress_y[e] = compress_y.size();
    ll grid[2*N_LIMIT+1][2*N_LIMIT+1];
    for (int i = 0; i < N; i++) {
        grid[compress_x[pts[i].first]+1][compress_y[pts[i].second]+1] += weights[i];
    }

    // 2D prefix sum
    for (int i = 1; i <= 2*N_LIMIT; i++) {
        for (int j = 1; j <= 2*N_LIMIT; j++) {
            grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1];
        }
    }

    // check all compressed positions as lower left corner
    ll result = 0;
    for (auto &x : coords_x) {
        if (!compress_x.count(x+W)) continue;
        for (auto &y : coords_y) {
            if (!compress_y.count(y+H)) continue;
            ll value = grid[compress_x[x+W]][compress_y[y+H]]
                     - grid[compress_x[x]][compress_y[y+H]]
                     - grid[compress_x[x+W]][compress_y[y]]
                     + grid[compress_x[x]][compress_y[y]];
            result = max(result, value);
        }
    }
    cout << result << endl;
}
