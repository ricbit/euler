import euler
import math
import sys
import itertools

def cycles(p):
  size = math.floor(math.log(p, 10) + 1)
  for i in range(size):
    yield p
    last = p % 10
    p = p // 10 + (last * 10 ** (size - 1))

primes = list(euler.sieve(10**6))
circular = set([2, 3, 5, 7])
seen = set()
for size in range(2, 7):
  for plist in itertools.product([1, 3, 7, 9], repeat=size):
    p = int("".join(str(i) for i in plist))
    if p in circular or p in seen:
      continue
    if all(c in primes for c in cycles(p)):
      circular.update(cycles(p))
    else:
      seen.update(cycles(p))
print(len(circular)) 
