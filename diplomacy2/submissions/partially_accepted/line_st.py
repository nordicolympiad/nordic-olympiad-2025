import heapq
class FenwickTree:
    def __init__(self, size):
        self.n = size
        self.s = [0] * (self.n + 2)  # 1-based indexing

    def update(self, x, val):
        x += 1  # Convert to 1-based index
        while x <= self.n:
            self.s[x] += val
            x += x & -x

    def query(self, x):
        x += 1
        res = 0
        while x > 0:
            res += self.s[x]
            x -= x & -x
        return res

    def lower_bound(self, sum):
        if sum <= 0: 
            return -1
        pos = 0
        pw = 1 << 25
        while pw:
            if pos + pw <= self.n and self.s[pos + pw] < sum:
                pos += pw
                sum -= self.s[pos]
            pw //= 2
        return pos

class SegmentTree:
    def __init__(self, size):
        self.n = size
        self.t = [0] * (4 * self.n)
        self.lazy = [1] * (4 * self.n)

    def push(self, v):
        if self.lazy[v] != 1:
            self.t[2*v] *= self.lazy[v]
            self.lazy[2*v] *= self.lazy[v]
            self.t[2*v+1] *= self.lazy[v]
            self.lazy[2*v+1] *= self.lazy[v]
            self.lazy[v] = 1

    def update_point(self, v, tl, tr, pos, inc):
        if tl == tr:
            self.t[v] += inc
        else:
            self.push(v)
            tm = (tl + tr) // 2
            if pos <= tm:
                self.update_point(2*v, tl, tm, pos, inc)
            else:
                self.update_point(2*v+1, tm+1, tr, pos, inc)
            self.t[v] = self.t[2*v] + self.t[2*v+1]

    def flip_range(self, v, tl, tr, l, r):
        if tr < l or tl > r:
            return
        if l <= tl and tr <= r:
            self.t[v] *= -1
            self.lazy[v] *= -1
        else:
            self.push(v)
            tm = (tl + tr) // 2
            self.flip_range(2*v, tl, tm, l, r)
            self.flip_range(2*v+1, tm+1, tr, l, r)
            self.t[v] = self.t[2*v] + self.t[2*v+1]

    def update(self, pos, inc):
        self.update_point(1, 0, self.n-1, pos, inc)

    def flip(self, l, r):
        self.flip_range(1, 0, self.n-1, l, r)

    def query_total(self):
        return self.t[1]




n,q = map(int,input().split())

cnt = FenwickTree(n+1)
cnt.update(1, n)  # Initially n intervals of size 1

D = SegmentTree(n+1)
if n % 2 == 1:
    D.update(1, 1)

pq = []
it = FenwickTree(n+1)
st = list(range(n))

for i in range(n):
    it.update(i,1)

def mal(sz,cf):
    ttl = cnt.query(n)
    sml = cnt.query(sz)
    cc = (1 - 2 * ((ttl - sml) % 2)) * sz
    cnt.update(sz, cf)
    D.flip(0, sz)
    D.update(sz, cc)

ccnt = n

for _ in range(q):
    s = input().split()
    cmd = s[0]
    if cmd == 'a':
        u,v,p = map(int,s[1:])
        u -= 1
        v -= 1
        if u +1 != v:
            continue
        pu = it.lower_bound(it.query(u-1) + 1)
        pv = it.lower_bound(it.query(v-1) + 1)

        if pu != pv:
            ccnt -= 1
            su = pu - st[pu] + 1
            sv = pv - st[pv] + 1
            it.update(pu,-1)
            
            st[pv] = st[pu]
            st[pu] = -1

            mal(su, -1)
            mal(sv, -1)
            mal(su+sv, 1)
        heapq.heappush(pq, (-p, u, v))
    elif cmd == 'r':
        ccnt += 1
        p_neg, u, v = heapq.heappop(pq)
        p = -p_neg

        pp = it.lower_bound(it.query(u) + 1)

        it.update(u,1)
        st[u] = st[pp]
        st[pp] = v

        su = u-st[u] + 1
        sv = pp-st[pp] + 1
        ts = su + sv
        mal(ts,-1)
        mal(su,1)
        mal(sv,1)
    elif cmd == 'd':
        print(D.query_total(),flush=False)
