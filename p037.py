import euler
import itertools

primes = list(euler.sieve(10**6))

def check(s):
  if s == '':
    return True
  return int(s) in primes

def truncatable(p):
  s = str(p)
  for i in range(len(s)):
    if not check(s[:i]):
      return False
    if not check(s[i:]):
      return False
  return True

def iterprimes():
  for p in primes:
    if p <= 7:
      continue
    if truncatable(p):
      yield p

print(sum(itertools.islice(iterprimes(), 0, 11)))
