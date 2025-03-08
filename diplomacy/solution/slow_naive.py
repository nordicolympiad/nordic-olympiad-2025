n,q = map(int,input().split())

vis = []
con = [[] for _ in range(n)]

def cc(u):
    if u in vis:
        return 0
    vis.append(u)
    r = 1
    for v in con[u]:
        r += cc(v)
    return r

edgs = []

for i in range(q):
    inp = input().split()
    if inp[0] == "a":
        u,v,p = map(int,inp[1:])
        u -= 1
        v -= 1
        p = int(p)
        con[u].append(v)
        con[v].append(u)
        edgs.append((u,v,p))

    if inp[0] == "r":
        mp = edgs[0][2]
        mj = 0
        for j,edg in enumerate(edgs):
            if edg[2] > mp:
                mj = j
                mp = edg[2]
        u,v,_ = edgs[mj]
        edgs.pop(mj)
        con[u].remove(v)
        con[v].remove(u)

    if inp[0] == "d":
        vis = []
        ccs = []
        for i in range(n):
            if i not in vis:
                ccs.append(cc(i))
        ccs.sort(reverse=True)
        ss = 0
        for i in range(len(ccs)):
            ss += (-1)**(i%2) * ccs[i]
        print(ss,flush=True)