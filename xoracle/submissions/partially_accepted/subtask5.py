#!/usr/bin/python3
N, Q = map(int, input().split())
v = [0] * N

for i in range(1, N):
	print(f"? 1 {i+1}")
	v[i] = int(input())

for i in range(N):
	sm = sum(v[i] ^ v[j] ^ 1 for j in range(N))
	if sm != 2 * N - 2 or any(v[i] ^ v[j] ^ 1 == 0 for j in range(N)):
		continue
	print('!', *[(v[i] ^ v[j] ^ 1) for j in range(N)])
	break
