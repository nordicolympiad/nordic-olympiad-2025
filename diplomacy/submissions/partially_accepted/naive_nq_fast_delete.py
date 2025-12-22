from heapq import heappush, heappop
import sys
sys.setrecursionlimit(500000)
n,q = map(int,input().split())

vis = [0]*n
con = [set() for i in range(n)]

def cc(u):
    if vis[u]:
        return 0
    vis[u] = 1
    r = 1
    for v in con[u]:
        r += cc(v)
    return r

prs = []

for i in range(q):
    inp = input().split()
    if inp[0] == "a":
        u,v,p = map(int,inp[1:])
        u = int(u) - 1
        v = int(v) - 1
        p = int(p)
        con[u].add(v)
        con[v].add(u)
        heappush(prs,(-p,u,v))

    if inp[0] == "r":
        _,u,v = heappop(prs)
        con[u].remove(v)
        con[v].remove(u)

    if inp[0] == "d":
        vis = [0]*n
        ccs = []
        for i in range(n):
            if not vis[i]:
                ccs.append(cc(i))
        ccs.sort(reverse=True)
        ss = 0
        for i in range(len(ccs)):
            ss += (-1)**(i%2) * ccs[i]
        print(ss,flush=True)