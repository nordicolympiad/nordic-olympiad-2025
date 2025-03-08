N, Q = map(int, input().split())
cnt = [0 for _ in range(N+1)]
cnt[0] = 1
for i in range(1, N):
	print(f"? 1 {i+1}", flush=True)
	cnt[int(input())] += 1
mx = 0
sec = 1
if cnt[0] < cnt[1]:
	mx, sec = sec, mx
for i in range(2, N+1):
	if cnt[i] > cnt[mx]:
		sec = mx
		mx = i
	elif cnt[i] > cnt[sec]:
		sec = i
for x in [mx, sec]:
	sm = 0
	for i in range(N+1):
		sm += cnt[i] * (i ^ x ^ 1)
	if sm != 2 * N - 2 or any(i ^ x ^ 1 == 0 and cnt[i] for i in range(N+1)):
		continue
	print('!', end=" ")
	for i in range(N+1):
		for _ in range(cnt[i]):
			print(i ^ x ^ 1, end=" ")
	print("", flush=True)
	break
