import euler
import itertools

primes = set(euler.sieve(3 * 10**6))

def getmax(a, b):
  for n in itertools.count(0):
    if (n * n + a * n + b) not in primes:
      return n

ans = (0, 0, 0)
for a in range(-999, 1000):
  for b in range(-1000, 1001):
    current = (getmax(a, b), a, b)
    if ans[0] < current[0]:
      ans = current
      print(ans)
print(ans[1] * ans[2])
