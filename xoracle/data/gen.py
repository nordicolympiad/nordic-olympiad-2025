z = set()
N = 100000
T = 49999
while len(z) < T:
	z.add(int(input()))
L = list(z)
print(6)
print(N, N-1)
j = 0
for i in range(T):
	while j in z:
		j += 1
	print(L[i], j)
	if i + 1 < T:
		print(L[i], L[i + 1])
	j += 1
while j in z:
	j += 1
print(L[0], j)
j += 1
while j in z:
	j += 1
print(L[-1], j)
