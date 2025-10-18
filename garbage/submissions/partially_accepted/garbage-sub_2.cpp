#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define XY_LIMIT 2000

int main() {
    // read input
    int N, W, H;
    cin >> N >> W >> H;
    ll grid[2*XY_LIMIT+1][2*XY_LIMIT+1];
    for (int i = 0; i < N; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        grid[x+1][y+1] += w;
    }

    // 2D prefix sum
    for (int i = 1; i <= 2*XY_LIMIT; i++) {
        for (int j = 1; j <= 2*XY_LIMIT; j++) {
            grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1];
        }
    }

    // check all positions for lower left corner
    ll result = 0;
    for (int i = 0; i < XY_LIMIT; i++) {
        for (int j = 0; j < XY_LIMIT; j++) {
            ll value = grid[i+W][j+H] - grid[i][j+H] - grid[i+W][j] + grid[i][j];
            result = max(result, value);
        }
    }
    cout << result << endl;
}
