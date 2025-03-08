XY_LIMIT = 1000000000

class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class node:
    def __init__(self, low, high):
        self.low = low
        self.high = high
        self.val = 0
        self.left = None
        self.right = None

    def insert(self, pos, val):
        self.val += val
        if (self.low == self.high): return

        mid = (self.low + self.high) // 2
        if (pos <= mid):
            if (self.left == None): self.left = node(self.low, mid)
            self.left.insert(pos, val)
        else:
            if (self.right == None): self.right = node(mid+1, self.high)
            self.right.insert(pos, val)

    def sum(self, l, h):
        if (h < self.low or l > self.high): return 0
        if (l <= self.low and h >= self.high): return self.val

        res = 0
        if (self.left != None): res += self.left.sum(l, h)
        if (self.right != None): res += self.right.sum(l, h)
        return res

class node2d:
    def __init__(self, low, high):
        self.low = low
        self.high = high
        self.tree = node(0, XY_LIMIT-1)
        self.left = None
        self.right = None

    def insert(self, x, y, val):
        self.tree.insert(y, val)
        if (self.low == self.high): return

        mid = (self.low + self.high) // 2
        if (x <= mid):
            if (self.left == None): self.left = node2d(self.low, mid)
            self.left.insert(x, y, val)
        else:
            if (self.right == None): self.right = node2d(mid+1, self.high)
            self.right.insert(x, y, val)

    def sum(self, l, r, b, t):
        if (r < self.low or l > self.high): return 0
        if (l <= self.low and r >= self.high): return self.tree.sum(b, t)

        res = 0
        if (self.left != None): res += self.left.sum(l, r, b, t)
        if (self.right != None): res += self.right.sum(l, r, b, t)
        return res

# read input
N, W, H = map(int, input().split())
pts = []
tree = node2d(0, XY_LIMIT-1)
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, y))
    tree.insert(x, y, w)

# check all pairs of points as lower boundaries
result = 0
for l in range(N):
    for b in range(N):
        value = tree.sum(pts[l].x, min(XY_LIMIT-1, pts[l].x + W - 1),
                         pts[b].y, min(XY_LIMIT-1, pts[b].y + H - 1))
        result = max(result, value)
print(result)
