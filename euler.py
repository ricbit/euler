import math
import itertools
import functools

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

def sum_of_divisors(n):
  return math.prod((p ** (coef + 1) - 1) // (p - 1) for p, coef in factor(n))

def collatz_path(n):
  yield n
  while n != 1:
    if n % 2 == 0:
      n //= 2
    else:
      n = 3 * n + 1
    yield n

def sieve(n = 10 ** 8):
  primes = [True] * n
  limit = math.isqrt(n) + 1
  for i in range(2, limit):
    if not primes[i]:
      continue
    yield i
    for j in range(i * i, n, i):
      primes[j] = False
  for i in range(limit, n):
    if primes[i]:
      yield i

def first(iterator):
  return list(itertools.islice(iterator, 0, 1))[0]

def totient(n):
  return math.prod(p ** (coef - 1) * (p - 1) for p, coef in factor(n))
   
def take(it, n):
  return list(itertools.islice(it, n))

def chunked(it, n):
  return iter(functools.partial(take, iter(it), n), [])

def digits(n):
  return math.ceil(math.log(1 + n, 10))

def count(it):
  ans = 0
  for i in it:
    ans += 1
  return ans

def sumdigits(n, e = 1):
  ans = 0
  while n > 0:
    ans += (n % 10) ** e
    n //= 10
  return ans

