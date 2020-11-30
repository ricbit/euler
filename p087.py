import itertools
import euler
import math

M = 50 * 10**6
primes = list(euler.sieve(math.ceil(M ** 0.5)))

def primepower(power):
  for p in primes:
    yield p ** power

ans = set()

L = M
def search(current, power):
  if power == 1:
    yield current
    return
  for p in itertools.takewhile(lambda p: current + p <= L, primepower(power)):
    yield from search(current + p, power - 1)

print(len(set(search(0, 4))))
    
