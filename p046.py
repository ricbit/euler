import euler
import itertools

M = 10**6
primes = set(euler.sieve(M))

def check(c):
  for i in itertools.count(1):
    if 2 * i * i > c:
      return False
    p = c - 2 * i * i
    if p in primes:
      return True

for c in range(9, M, 2):
  if c in primes:
    continue
  if not check(c):
    print(c)
    break
