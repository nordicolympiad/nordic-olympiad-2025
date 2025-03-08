class point:
    def __init__(self, x, y, w):
        self.x = x
        self.y = y
        self.w = w

# read input
N, W, H = map(int, input().split())
pts = []
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, y, w))

# check all pairs of points as lower boundaries
result = 0
for l in range(N):
    for b in range(N):
        value = 0
        for i in range(N):
            if (pts[i].x >= pts[l].x and pts[i].x < pts[l].x + W and
                pts[i].y >= pts[b].y and pts[i].y < pts[b].y + H):
                    value += pts[i].w
        result = max(result, value)
print(result)
