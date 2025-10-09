#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;

#define N_MAX (200000ll)
#define XY_MAX (1000000000ll)
#define X_MAX XY_MAX
#define Y_MAX XY_MAX
#define WIDTH_MAX XY_MAX
#define HEIGHT_MAX XY_MAX
#define WEIGHT_MAX (1000000000ll)

ll from0(ll ex_limit) {
    assert(ex_limit > 0);
    return rnd.next(ex_limit);
}

ll from1(ll in_limit) {
    return 1+from0(in_limit);
}

class xy_generator {
public:
    ll x_limit, y_limit; // exclusive
    xy_generator(ll xy_limit)
        : x_limit(xy_limit), y_limit(xy_limit) {}
    virtual pair<ll, ll> get() = 0;
};

class w_generator {
public:
    ll w_limit; // inclusive
    w_generator(ll w_limit)
        : w_limit(w_limit) {}
    virtual ll get() = 0;
};

class xy_uniform : public xy_generator {
    using xy_generator::xy_generator;
public:
    pair<ll, ll> get() {
        return {from0(x_limit), from0(y_limit)};
    }
};

class xy_hotspots : public xy_generator {
    ll hotspot_cnt, hotspot_size;
    vector<pair<ll, ll>> hotspots;
public:
    xy_hotspots(ll xy_limit, ll hotspot_cnt, ll hotspot_size)
        : xy_generator(xy_limit), hotspot_cnt(hotspot_cnt), hotspot_size(hotspot_size) {
        ll x_max = x_limit - hotspot_size + 1;
        ll y_max = y_limit - hotspot_size + 1;
        hotspots = vector<pair<ll, ll>>(hotspot_cnt);
        for (auto &e : hotspots) e = {from0(x_max), from0(y_max)};
    }
    pair<ll, ll> get() {
        pair<ll, ll> pt = hotspots[from0(hotspot_cnt)];
        return {pt.first + from0(hotspot_size), pt.second + from0(hotspot_size)};
    }
};

class xy_border : public xy_generator {
    using xy_generator::xy_generator;
public:
    pair<ll, ll> get() {
        if (from0(2)) { // vertical border
            return {from0(2) * (x_limit-1), from0(y_limit)};
        }
        else { // horizontal border
            return {from0(x_limit), from0(2) * (y_limit-1)};
        }
    }
};

class xy_anti_random : public xy_generator {
    ll bait_cnt, border_w, border_h;
    vector<pair<ll, ll>> bait;
    pair<ll, ll> best;
    bool dissolve;

    vector<ll> counts;
    ll max_count, border_count;
    ll dl, dr, db, dt;
public:
    xy_anti_random(ll xy_limit, ll bait_cnt, ll border_w, ll border_h, bool dissolve)
        : xy_generator(xy_limit), bait_cnt(bait_cnt), border_w(border_w), border_h(border_h), dissolve(dissolve),
          max_count(0), border_count(0), dl(-5), dr(-5), db(-5), dt(-5) {
        ll x_max = x_limit - border_w + 1;
        ll y_max = y_limit - border_h + 1;
        bait = vector<pair<ll, ll>>(bait_cnt);
        for (auto &e : bait) e = {from0(x_max), from0(y_max)};
        best = {from0(x_max), from0(y_max)};

        counts = vector<ll>(bait_cnt);
    }
    pair<ll, ll> get() {
        if (border_count < max_count + 100 || from0(bait_cnt+1) == 0) { // border
            border_count++;
            if (from0(2)) { // vertical border
                ll xOffset = from0(2) * (border_w-1);
                if (dissolve) {
                    if (xOffset == 0) xOffset += dl++;
                    else xOffset -= dr++;
                }
                return {min(max(best.first + xOffset, 0ll), x_limit-1),
                        min(max(best.second + (border_h-1) / 4 + from0(max(1ll, (border_h-1) / 2)), 0ll), y_limit-1)};
            }
            else { // horizontal border
                ll yOffset = from0(2) * (border_h-1);
                if (dissolve) {
                    if (yOffset == 0) yOffset += db++;
                    else yOffset -= dt++;
                }
                return {min(max(best.first + (border_w-1) / 4 + from0(max(1ll, (border_w-1) / 2)), 0ll), x_limit-1),
                        min(max(best.second + yOffset, 0ll), y_limit-1)};
            }
        }
        else { // bait
            ll id = from0(bait_cnt);
            max_count = max(max_count, ++counts[id]);
            return {bait[id].first + from0(border_w), bait[id].second + from0(border_h)};
        }
    }
};

class xy_mix : public xy_generator {
    xy_uniform uniform;
    xy_hotspots hotspots;
    xy_border border;
    xy_anti_random anti_random;
    vector<xy_generator*> gens;
public:
    xy_mix(ll xy_limit, ll hotspot_cnt, ll hotspot_size, ll bait_cnt, ll border_w, ll border_h, bool dissolve)
        : xy_generator(xy_limit), uniform(xy_limit), hotspots(xy_limit, hotspot_cnt, hotspot_size),
          border(xy_limit), anti_random(xy_limit, bait_cnt, border_w, border_h, dissolve) {
        gens = vector<xy_generator*>();
        gens.push_back(&uniform);
        gens.push_back(&hotspots);
        gens.push_back(&border);
        gens.push_back(&anti_random);
    }
    pair<ll, ll> get() {
        return gens[from0(gens.size())]->get();
    }
};

class w_uniform : public w_generator {
    using w_generator::w_generator;
public:
    ll get() {
        return from1(w_limit);
    }
};

class w_constant : public w_generator {
    using w_generator::w_generator;
public:
    ll get() {
        return w_limit;
    }
};

class w_extremes : public w_generator {
    using w_generator::w_generator;
public:
    ll get() {
        if (from0(10) == 0) {
            return max(1ll, w_limit-1 - from0(4));
        }
        else {
            return from1(2);
        }
    }
};

void gen(ll N, ll W, ll H, xy_generator &xy, w_generator &w) {
    assert(1 <= N && N <= N_MAX);
    assert(1 <= W && W <= WIDTH_MAX);
    assert(1 <= H && H <= HEIGHT_MAX);

    cout << N << ' ' << W << ' ' << H << '\n';
    for (int i = 0; i < N; i++) {
        pair<ll, ll> coords = xy.get();
        assert(0 <= coords.first && coords.first < X_MAX);
        assert(0 <= coords.second && coords.second < Y_MAX);

        ll weight = w.get();
        assert(1 <= weight && weight <= WEIGHT_MAX);
        
        cout << coords.first << ' ' << coords.second << ' ' << weight << '\n';
    }
}

int _argc, argid = 1;
char **_argv;
char *read_next() {
    argid++;
    assert(argid < _argc);
    return _argv[argid];
}

// N, xy_generator, xy_limit(ex), (xy_params), w_generator, w_limit(in)
// N, xy_generator, xy_limit(ex), (xy_params), w_generator, w_limit(in), H
// N, xy_generator, xy_limit(ex), (xy_params), w_generator, w_limit(in), W, H
int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
    _argc = argc;
    _argv = argv;

    ll N = atoll(read_next());

    string xy_class(read_next());
    ll xy_limit = atoll(read_next());
    xy_generator *xy;
    if (xy_class == "xy_uniform") {
        xy = new xy_uniform(xy_limit);
    }
    else if (xy_class == "xy_hotspots") {
        ll hotspot_cnt = atoll(read_next());
        ll hotspot_size = atoll(read_next());
        xy = new xy_hotspots(xy_limit, hotspot_cnt, hotspot_size);
    }
    else if (xy_class == "xy_border") {
        xy = new xy_border(xy_limit);
    }
    else if (xy_class == "xy_anti_random") {
        ll bait_cnt = atoll(read_next());
        ll border_w = atoll(read_next());
        ll border_h = atoll(read_next());
        ll dissolve = atoll(read_next());
        assert(dissolve == 0 || dissolve == 1);
        xy = new xy_anti_random(xy_limit, bait_cnt, border_w, border_h, dissolve);
    }
    else if (xy_class == "xy_mix") {
        ll hotspot_cnt = atoll(read_next());
        ll hotspot_size = atoll(read_next());
        ll bait_cnt = atoll(read_next());
        ll border_w = atoll(read_next());
        ll border_h = atoll(read_next());
        ll dissolve = atoll(read_next());
        assert(dissolve == 0 || dissolve == 1);
        xy = new xy_mix(xy_limit, hotspot_cnt, hotspot_size, bait_cnt, border_w, border_h, dissolve);
    }
    else assert(false);
    assert(xy != nullptr);

    string w_class(read_next());
    ll w_limit = atoll(read_next());
    w_generator *w;
    if (w_class == "w_uniform") {
        w = new w_uniform(w_limit);
    }
    else if (w_class == "w_constant") {
        w = new w_constant(w_limit);
    }
    else if (w_class == "w_extremes") {
        w = new w_extremes(w_limit);
    }
    else assert(false);
    assert(w != nullptr);

    int W = from1(xy_limit);
    int H = from1(xy_limit);
    if (argid+2 < argc) {
        W = atoll(read_next());
        H = atoll(read_next());
    }
    else if (argid+1 < argc) {
        H = atoll(read_next());
    }

    gen(N, W, H, *xy, *w);
}
