class point:
    def __init__(self, x, w):
        self.x = x
        self.w = w

    def __lt__(self, obj):
        return self.x < obj.x

# read input
N, W, H = map(int, input().split())
pts = []
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, w))
pts.sort()

# two pointers
r = 0
result = 0
running_weight = 0
for l in range(N):
    left_border = pts[l].x
    right_border = left_border + W - 1
    while (r < N and pts[r].x <= right_border):
        running_weight += pts[r].w
        r += 1
    result = max(result, running_weight)
    running_weight -= pts[l].w
print(result)
