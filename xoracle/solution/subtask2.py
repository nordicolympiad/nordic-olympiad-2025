N, Q = map(int, input().split())
a, b, c, d = 1, 1, 1, 1
v = [0] * N

for i in range(1, N):
	print(f"? 1 {i+1}")
	v[i] = int(input())
	
	if v[i] == 1:
		a, d = 0, 0
	if v[i] == 2:
		b, d = 0, 0
	if v[i] == 3:
		c, d = 0, 0
	if v[i] == 5:
		b, c = 0, 0
	if v[i] == 6:
		a, c = 0, 0
	if v[i] == 7:
		a, b = 0, 0

x = 0
if a:
	x = 1
if b:
	x = 2
if c:
	x = 3
if d:
	x = 4

print('!', *[d ^ x for d in v])
