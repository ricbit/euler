N = 100000
M = 1000000
part = [0] * N

part[0] = part[1] = 1
for n in range(2, N - 1):
  s = 1
  for k in range(1, n + 1):
    a = n - k * (3 * k - 1) // 2
    b = n - k * (3 * k + 1) // 2
    if a < 0 and b < 0:
      break
    pa = part[a] if a >= 0 else 0
    pb = part[b] if b >= 0 else 0
    part[n] = (part[n] + s * (pa + pb)) % M
    s *= -1
  if part[n] == 0:
    print(n, part[n]) 
    break



