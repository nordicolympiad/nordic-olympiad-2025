#!/usr/bin/python3
class point:
    def __init__(self, x, y, w):
        self.x = x
        self.y = y
        self.w = w

    def __lt__(self, obj):
        return self.x < obj.x

class node:
    def __init__(self, low, high):
        self.low = low
        self.high = high
        self.val = 0
        self.laz = 0
        self.left = None
        self.right = None

    def insert(self, pos):
        if (self.low == self.high): return

        mid = (self.low + self.high) // 2
        if (pos <= mid):
            if (self.left == None): self.left = node(self.low, mid)
            self.left.insert(pos)
        else:
            if (self.right == None): self.right = node(mid+1, self.high)
            self.right.insert(pos)

    def prop(self):
        if (self.left != None): self.left.laz += self.laz
        if (self.right != None): self.right.laz += self.laz
        self.val += self.laz
        self.laz = 0
	
    def recalc(self):
        if (self.left == None and self.right == None): return
        self.val = -(2**62)
        if (self.left != None): self.val = max(self.val, self.left.val)
        if (self.right != None): self.val = max(self.val, self.right.val)

    def add_range(self, l, h, val):
        if (h < self.low or l > self.high):
            self.prop()
            return
        if (l <= self.low and h >= self.high):
            self.laz += val
            self.prop()
            return

        self.prop()
        if (self.left != None): self.left.add_range(l, h, val)
        if (self.right != None): self.right.add_range(l, h, val)
        self.recalc()

# read input
N, W, H = map(int, input().split())
pts = []
seg_tree = node(0, 1000000000)
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, y, w))
    seg_tree.insert(y)
    seg_tree.insert(y + H - 1)
pts.sort()

# two pointers
r = 0
result = 0
for l in range(N):
    left_border = pts[l].x
    right_border = left_border + W - 1
    while (r < N and pts[r].x <= right_border):
        seg_tree.add_range(pts[r].y, pts[r].y + H - 1, pts[r].w)
        r += 1
    result = max(result, seg_tree.val)
    seg_tree.add_range(pts[l].y, pts[l].y + H - 1, -pts[l].w)
print(result)
