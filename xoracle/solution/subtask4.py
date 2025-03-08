N, Q = map(int, input().split())
group = [-1] * N
q = [[-1] * N for _ in range(N)]

def query(v, u):
	if q[v][u] != -1:
		return q[v][u]
	print(f"? {v+1} {u+1}")
	x = int(input())
	q[v][u] = q[u][v] = x
	if x == -1:
		exit(0)
	return x

g = 0
v = []
cnt = {}

for i in range(N):
	for j in v:
		if query(i, j) == 0:
			group[i] = group[j]
			break
	if group[i] == -1:
		group[i] = g
		g += 1
		v.append(i)
	cnt[group[i]] = cnt.get(group[i], 0) + 1

for i in v:
	sm = sum(cnt[group[j]] * (query(j, i) ^ 1) for j in v)
	if sm != 2 * N - 2 or any(cnt[group[j]] > 0 and query(j, i) ^ 1 == 0 for j in v):
		continue
	print('!', end=' ')
	for j in v:
		for _ in range(cnt[group[j]]):
			print(query(j, i) ^ 1, end=' ')
	print()
	break

