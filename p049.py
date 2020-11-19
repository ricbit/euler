import euler

primes = [p for p in euler.sieve(10000) if p >= 1000]
primeset = set(primes)

def check(a, b, c):
  sa, sb, sc = [list(sorted(str(i))) for i in [a, b, c]]
  return sa == sb == sc

for i, p1 in enumerate(primes):
  for i2 in range(i + 1, len(primes)):
    p2 = primes[i2]
    p3 = p1 + 2 * (p2 - p1)
    if p3 in primeset and check(p1, p2, p3):
      print(p1, p2, p3)
    
