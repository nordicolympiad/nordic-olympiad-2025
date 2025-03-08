#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<double>
#define vcom vector<com>
#define vld vector<ld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define endl '\n'
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())

const int inf = 1e9;
struct FT {
    int n;
	vector<ll> s;
	FT(int _n) : n(_n), s(n+1) {}
	void update(int x,int val) { 
        x++;  
        while(x<=n) {
            s[x]+=val;
            x+=(x&-x);  
        } 
    }

	ll query(int x) {
		ll res = 0;
        x++;
        while(x > 0) {
            res += s[x];
            x -= x&-x;
        }
		return res;
	}
};

struct ST {
    int n;
    int tz;
    vi t, lazy;
    ST(int _n) : n(_n), tz(4*n), t(tz), lazy(tz,1) {}
    
    void push(int v) {
        t[v*2] *= lazy[v];
        lazy[v*2] *= lazy[v];
        t[v*2+1] *= lazy[v];
        lazy[v*2+1] *= lazy[v];
        lazy[v] = 1;
    }
    
    void update(int v, int tl, int tr, int i, int inc) {
        if (i < tl || i > tr) return;
        if (tl == i && tr == i) {
            t[v] += inc;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, i, inc);
            update(v*2+1, tm+1, tr, i, inc);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
    void update(int i, int inc) {
        update(1,0,n-1,i,inc);
    }
    
    void flip(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) return;
        if (l <= tl && tr <= r) {
            lazy[v] *= -1;
            t[v] *= -1;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            flip(v*2, tl, tm, l, r);
            flip(v*2+1, tm+1, tr, l, r);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
    void flip(int l, int r) {
        flip(1,0,n-1,l,r);
    }
    
    int query() {
        return t[1];
    }
};

struct UF {
    vi p,s;
    vii a;
    UF(int n) : p(n), s(n,1) {
        iota(ALL(p),0);
    }

    int find(int u) {
        return p[u] == u ? u : find(p[u]);
    }

    void uni(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) {
            a.pb({-1,-1});
            return;
        }
        if(s[u] > s[v]) swap(u,v);
        p[u] = v;
        s[v] += s[u];
        a.pb({u,v});
        return;
    }

    void undo() {
        int u,v;
        tie(u,v) = a.back();
        a.pop_back();
        if(u == -1) return;
        p[u] = u;
        s[v] -= s[u];
    }
};

FT cnt(0);
ST D(0);
UF C(0);
int n,q;
void mal(int sz,int cf) {
    int ttl = cnt.query(n);
    int sml = cnt.query(sz);
    int cc = (1-2*((ttl-sml)%2))*sz;
    cnt.update(sz,cf);

    D.flip(0,sz);
    D.update(sz,cc);

    //cout << " " << ttl << " " << sml << endl;
}

int main() {
    cin >> n >> q;
    cnt = FT(n+1);
    D = ST(n+1);
    C = UF(n);
    cnt.update(1,n);
    if(n % 2) {
        D.update(1,1);
    }
    vii stk;
    //cerr << " N " << D.query() << endl;
    FOR(i,q) {
        string c;
        cin >> c;
        if(c == "a") {
            int u,v,p;
            cin >> u >> v >> p;
            u--;
            v--;
            stk.pb({u,v});
            int pu = C.find(u);
            int pv = C.find(v);
            if(pu != pv) {
                int su = C.s[pu];
                int sv = C.s[pv];
                C.uni(u,v);
                mal(su,-1);
                mal(sv,-1);
                mal(su+sv,1);
            } else {
                C.uni(u,v);
            }
        } else if(c=="r") {
            C.undo();
            int u,v;
            tie(u,v) = stk.back();
            stk.pop_back();
            int pu = C.find(u);
            int pv = C.find(v);
            if(pu != pv) {
                int su = C.s[pu];
                int sv = C.s[pv];
                int ts = su+sv;
                mal(ts,-1);
                mal(su,1);
                mal(sv,1);
            }
        } else {
            cout << D.query() << endl;
        }
    }
}