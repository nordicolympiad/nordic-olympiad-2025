XY_LIMIT = 2000

# read input
N, W, H = map(int, input().split())
grid = [[0 for i in range(2*XY_LIMIT+1)] for j in range(2*XY_LIMIT+1)] # can be optimized
for i in range(N):
    x, y, w = map(int, input().split())
    grid[x+1][y+1] += w

# 2D prefix sum
for i in range(1, 2*XY_LIMIT+1):
    for j in range(1, 2*XY_LIMIT+1):
        grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1]

# check all positions for lower left corner
result = 0
for i in range(XY_LIMIT):
    for j in range(XY_LIMIT):
        value = grid[i+W][j+H] - grid[i][j+H] - grid[i+W][j] + grid[i][j]
        result = max(result, value)
print(result)
