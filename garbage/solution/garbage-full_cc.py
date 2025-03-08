import math

class point:
    def __init__(self, x, y_mn, y_mx, w):
        self.x = x
        self.y_mn = y_mn
        self.y_mx = y_mx
        self.w = w

    def __lt__(self, obj):
        return self.x < obj.x

class node:
    def __init__(self):
        self.val = 0
        self.lazy = 0

power_of_2 = 0
seg_tree = []

def prop(id):
    if (id < power_of_2):
        seg_tree[2 * id].lazy += seg_tree[id].lazy
        seg_tree[2 * id + 1].lazy += seg_tree[id].lazy
    seg_tree[id].val += seg_tree[id].lazy
    seg_tree[id].lazy = 0

def add_range(id, node_low, node_high, range_low, range_high, val):
    if (range_high < node_low or range_low > node_high):
        prop(id)
        return
    if (range_low <= node_low and range_high >= node_high):
        seg_tree[id].lazy += val
        prop(id)
        return

    prop(id)
    mid = (node_low + node_high) // 2
    add_range(2 * id, node_low, mid, range_low, range_high, val)
    add_range(2 * id + 1, mid + 1, node_high, range_low, range_high, val)
    seg_tree[id].val = max(seg_tree[2 * id].val, seg_tree[2 * id + 1].val)

# read input
N, W, H = map(int, input().split())
pts = []
coords_y = []
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, y, y + H - 1, w))
    coords_y.append(y)
    coords_y.append(y + H - 1)
coords_y.sort()
pts.sort()

# coordinate compression
compress_y = {}
for e in coords_y: compress_y.update({e: len(compress_y)})
for i in range(N):
    pts[i].y_mn = compress_y[pts[i].y_mn]
    pts[i].y_mx = compress_y[pts[i].y_mx]

# two pointers
power_of_2 = 2**math.ceil(math.log2(len(coords_y) + 10))
seg_tree = [node() for i in range(2 * power_of_2)]
result = 0
r = 0
for l in range(N):
    left_border = pts[l].x
    right_border = left_border + W - 1
    while (r < N and pts[r].x <= right_border):
        add_range(1, 0, power_of_2 - 1, pts[r].y_mn, pts[r].y_mx, pts[r].w)
        r += 1
    result = max(result, seg_tree[1].val)
    add_range(1, 0, power_of_2 - 1, pts[l].y_mn, pts[l].y_mx, -pts[l].w)
print(result)
