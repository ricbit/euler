import math
from collections import Counter

limit = 1500000
hist = Counter()
for n in range(1, 2 + math.isqrt(limit)):
  for m in range(n + 1, 2 + math.isqrt(limit), 2):
    if math.gcd(m, n) != 1:
      continue
    base = 2*m*(m+n)
    for k in range(1, 1 + limit // base):
      hist[k * base] += 1
print(len([k for k,v in hist.items() if v == 1 and k <= limit]))
