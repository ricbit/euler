import math
import itertools

def fibonacci():
  a, b = 1, 1
  yield a
  while True:
    yield b
    a, b = b, a + b

def is_prime(p):
  if p in [2, 3, 5]:
    return True
  if math.gcd(p, 30) > 1:
    return False
  for i in range(6, math.isqrt(p) + 1, 6):
    if p % (i + 1) == 0:
      return False
    if p % (i + 5) == 0:
      return False
  return True

def primes():
  known = [2, 3, 5]
  yield from known
  for i in itertools.count(6, 6):
    def check(p):
      sqrt = math.isqrt(p)
      if all(p % i != 0 for i in itertools.takewhile(lambda x: x <= sqrt, known)):
        known.append(p)
        yield p
    yield from check(i + 1)
    yield from check(i + 5)
  



