#include "validator.h"
using namespace std;
#include <queue>

void run() {
    int n = Int(1, Arg("maxn", 100000));
    Space();
    int q = Int(1, Arg("maxq", 500000));
    Endl();

    set<int> seen_page_counts;
    set<pair<int,int>> active_edges;
    priority_queue<tuple<int,int,int>> active_treaties;
    int num_d = 0;

    auto add = [&](int u, int v, int p) {
        assert(!seen_page_counts.count(p));
        seen_page_counts.insert(p);

        if (u>v) swap(u,v);
        assert(!active_edges.count(make_pair(u,v)));
        active_edges.insert(make_pair(u,v));
        active_treaties.emplace(p,u,v);
    };

    auto remove = [&]() {
        assert(active_treaties.size());
        auto [p,u,v] = active_treaties.top();
        active_treaties.pop();
        active_edges.erase(make_pair(u,v));
    };

    bool line = Arg("line", false);
    bool increasing_p = Arg("increasing_p", false);
    bool decreasing_p = Arg("decreasing_p", false);
    int last_p = -1;
    for (int i = 0; i < q; i++) {
        char type = Char();
        if (type == 'a') {
            Space();
            int u = Int(1, n);
            Space();
            int v = Int(1, n);
            Space();
            int p = Int(1, int(1e9));
            Endl();
            assert(u != v);

            u--; v--;
            add(u,v,p);

            if (increasing_p) {
                if (last_p != -1) {
                    assert(p > last_p);
                }
                last_p = p;
            }
            if (decreasing_p) {
                if (last_p != -1) {
                    assert(p < last_p);
                }
                last_p = p;
            }
            if (line) {
                assert(u+1 == v);
            }
        }
        else if (type == 'r' or type == 'd') {
            if (type == 'r') remove();
            if (type == 'd') num_d++;
            Endl();
        }
        else assert(0);
    }
    assert(num_d <= (int)Arg("maxd", q));
}

