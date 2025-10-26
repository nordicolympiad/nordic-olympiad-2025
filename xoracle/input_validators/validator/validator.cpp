#include "validator.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct UF {
    vi par;
    UF(int n) : par(n) {
        rep(i,0,n) par[i]=i;
    }
    int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        par[b] = a;
    }
};

void run() {
    // TODO: special1 and 2
    Int(1, 6); // test group
    Endl();
    bool special1 = Arg("special1", false);
    bool special2 = Arg("special2", false);

    string q_mode = Arg("q");
    int n = Int(1, Arg("maxn", int(1e5)));
    Space();
    int q = Int(1, int(1e5));
    Endl();
    if (q_mode=="n-1") assert(q==n-1);
    else if (q_mode=="n_squared") assert(q==n*n);
    else if (q_mode=="45000") assert(q==45000);
    else assert(false && "Unknown query mode");

    vi deg(n);
    UF uf(n);
    rep(i, 0, n-1) {
        int u = Int(0, n-1);
        Space();
        int v = Int(0, n-1);
        Endl();
        assert(uf.find(u)!=uf.find(v));
        uf.merge(u,v);

        deg[u]++;
        deg[v]++;
    }
    if (special1) {
        assert(*max_element(all(deg)) <= 3);
        int num_found = 0;
        num_found += find(all(deg), 1) != deg.end();
        num_found += find(all(deg), 2) != deg.end();
        num_found += find(all(deg), 3) != deg.end();
        assert(num_found == 3);
    }
    if (special2) {
        assert(*max_element(all(deg)) <= 4);
        int num_found = 0;
        num_found += find(all(deg), 1) != deg.end();
        num_found += find(all(deg), 2) != deg.end();
        num_found += find(all(deg), 3) != deg.end();
        num_found += find(all(deg), 4) != deg.end();
        assert(num_found >= 3);
    }
}

