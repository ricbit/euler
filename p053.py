import math

ans = 0
for n in range(1, 101):
  for r in range(n + 1):
    if math.comb(n, r) > 10**6:
      ans += 1
print(ans)
