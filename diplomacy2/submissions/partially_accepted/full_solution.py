from heapq import heappop, heappush
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

class UF:
    def __init__(self, n):
        self.p = list(range(n))  # Parent array
        self.s = [1] * n  # Size array
        self.a = []  # History for undo operation
    
    def find(self, u):
        if self.p[u] == u:
            return u
        return self.find(self.p[u])
    
    def uni(self, u, v):
        u, v = self.find(u), self.find(v)
        if u == v:
            self.a.append((-1, -1))
            return
        if self.s[u] > self.s[v]:
            u, v = v, u
        self.p[u] = v
        self.s[v] += self.s[u]
        self.a.append((u, v))
    
    def undo(self):
        if not self.a:
            return
        u, v = self.a.pop()
        if u == -1:
            return
        self.p[u] = u
        self.s[v] -= self.s[u]


class PQUF:
    def __init__(self,n):
        self.stk = []
        self.U = UF(n)
        self.ps = []
        self.tv = {}

    def find(self,u): 
        return self.U.find(u)

    def uni(self, u, v, p):
        self.U.uni(u,v)
        heappush(self.ps, (-p,len(self.stk)))
        self.tv[p] = len(self.stk)
        self.stk.append((p,u,v))

    def pop(self):
        while -self.ps[0][0] not in self.tv or self.tv[-self.ps[0][0]] != self.ps[0][1]: 
            heappop(self.ps)
        
        l = self.ps[0][1]

        ci = len(self.stk) 
        while(len(self.ps) and l < ci):
            p,lc = heappop(self.ps)
            p = -p
            if p not in self.tv or self.tv[p] != lc:
                continue
            l = min(l,lc)
            ci -= 2
        tbs = []
        for i in range(len(self.stk)-1,max(ci,0)-1,-1):
            tbs.append(self.stk.pop())
            self.U.undo()
            del self.tv[tbs[-1][0]]
        tbs.sort()
        for p,u,v in tbs:
            self.uni(u,v,p)

        self.U.undo()
        rp,ru,rv = self.stk.pop()
        del self.tv[rp]
        return ru,rv


n,q = map(int,input().split())

cnt = FenwickTree(n+1)
cnt.update(1, n)  # Initially n intervals of size 1

D = SegmentTree(n+1)
if n % 2 == 1:
    D.update(1, 1)

C = PQUF(n)

def mal(sz,cf):
    ttl = cnt.query(n)
    sml = cnt.query(sz)
    cc = (1 - 2 * ((ttl - sml) % 2)) * sz
    cnt.update(sz, cf)
    D.flip(0, sz)
    D.update(sz, cc)

for _ in range(q):
    s = input().split()
    cmd = s[0]
    if cmd == 'a':
        u,v,p = map(int,s[1:])
        u -= 1
        v -= 1
        pu = C.find(u)
        pv = C.find(v)

        if pu != pv:
            su = C.U.s[pu]
            sv = C.U.s[pv]
            mal(su, -1)
            mal(sv, -1)
            mal(su+sv, 1)
        C.uni(u,v,p)
    elif cmd == 'r':
        u,v = C.pop()
        pu = C.find(u)
        pv = C.find(v)
        if pu != pv:
            su = C.U.s[pu]
            sv = C.U.s[pv]
            mal(su+sv, -1)
            mal(su, 1)
            mal(sv, 1)
    elif cmd == 'd':
        print(D.query_total(),flush=True)
