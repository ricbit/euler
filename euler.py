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
  
def factor(p):  
  for i in range(2, math.isqrt(p) + 1):
    coef = 0
    while p % i == 0:
      coef += 1
      p //= i
    if coef > 0:
      yield (i, coef)
  if p > 1:
    yield (p, 1)
    
def number_of_divisors(p):
  return math.prod(coef + 1 for p, coef in factor(p))

def collatz_path(n):
  yield n
  while n != 1:
    if n % 2 == 0:
      n //= 2
    else:
      n = 3 * n + 1
    yield n
