N, Q = map(int, input().split())
group = [-1] * N
q = [[-1] * N for _ in range(N)]

def query(v, u):
	if q[v][u] != -1:
		return q[v][u]
	print(f"? {v+1} {u+1}")
	q[v][u] = int(input())
	if q[v][u] == -1:
		exit(0)
	return q[v][u]

for i in range(N):
	sm = sum(query(i, j) ^ 1 for j in range(N))
	if sm != 2 * N - 2 or any(query(i, j) ^ 1 == 0 for j in range(N)):
		continue
	print('!', *[(query(i, j) ^ 1) for j in range(N)])
	break
