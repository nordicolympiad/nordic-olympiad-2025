N_LIMIT = 2000

class point:
    def __init__(self, x, y, w):
        self.x = x
        self.y = y
        self.w = w

# read input
N, W, H = map(int, input().split())
pts = []
coords_x = []
coords_y = []
for i in range(N):
    x, y, w = map(int, input().split())
    pts.append(point(x, y, w))
    coords_x.append(x)
    coords_x.append(x + W)
    coords_y.append(y)
    coords_y.append(y + H)
coords_x.sort()
coords_y.sort()

# coordinate compression
compress_x = {}
compress_y = {}
for e in coords_x: compress_x.update({e: len(compress_x)})
for e in coords_y: compress_y.update({e: len(compress_y)})
grid = [[0 for i in range(2*N_LIMIT+1)] for j in range(2*N_LIMIT+1)] # can be optimized
for i in range(N):
    grid[compress_x[pts[i].x]+1][compress_y[pts[i].y]+1] += pts[i].w

# 2D prefix sum
for i in range(1, 2*N_LIMIT+1):
    for j in range(1, 2*N_LIMIT+1):
        grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1]

# check all compressed positions as lower left corner
result = 0
for x in coords_x:
    if (x+W not in compress_x): continue
    for y in coords_y:
        if (y+H not in compress_y): continue
        value = grid[compress_x[x+W]][compress_y[y+H]]
        value -= grid[compress_x[x]][compress_y[y+H]]
        value -= grid[compress_x[x+W]][compress_y[y]]
        value += grid[compress_x[x]][compress_y[y]]
        result = max(result, value)
print(result)
