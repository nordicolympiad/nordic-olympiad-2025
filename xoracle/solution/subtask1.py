N, Q = map(int, input().split())
V = [0 for _ in range(N)]
for i in range(1, N):
	print(f"? 1 {i+1}")
	V[i] = int(input())
for i in range(4):
	if i in V:
		continue
	print("!", end="")
	for x in V:
		print(f" {i ^ x}", end="")
	print("", flush=True)
	break
