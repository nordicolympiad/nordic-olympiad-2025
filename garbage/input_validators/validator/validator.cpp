#include "validator.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int BILLION = 1e9;
void run() {
    bool hinf = Arg("hinf", false);
    int maxcoord = int(Arg("maxcoord", BILLION));
    int n = Int(1, int(Arg("maxn", int(1e5))));
    Space();
    int w = Int(1, maxcoord);
    Space();
    int h = Int(1, maxcoord);
    Endl();

    if (hinf) assert(h==BILLION);

    rep(i,0,n) {
        int x = Int(0, maxcoord);
        Space();
        int y = Int(0, maxcoord);
        Space();
        Int(1, BILLION);
        Endl();
    }
}

