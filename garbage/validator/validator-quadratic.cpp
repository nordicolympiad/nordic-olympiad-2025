#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;

#define N_MAX (2000ll)
#define XY_MAX (1000000000ll)
#define X_MAX XY_MAX
#define Y_MAX XY_MAX
#define WIDTH_MAX XY_MAX
#define HEIGHT_MAX XY_MAX
#define WEIGHT_MAX (1000000000ll)

struct point {
    int x, y, w;
};

int main() {
	registerValidation();
	ll N = inf.readInt(1, N_MAX, "N");
	inf.readSpace();
	ll W = inf.readInt(1, WIDTH_MAX, "W");
	inf.readSpace();
	ll H = inf.readInt(1, HEIGHT_MAX, "H");
	inf.readEoln();
	vector<point> points(N);
	for (int i = 0; i < N; i++) {
		points[i].x = inf.readInt(0, X_MAX-1, "x_i");
		inf.readSpace();
		points[i].y = inf.readInt(0, Y_MAX-1, "y_i");
		inf.readSpace();
		points[i].w = inf.readInt(1, WEIGHT_MAX, "w_i");
		inf.readEoln();
	}
	inf.readEof();
}
