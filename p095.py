import euler

primes = list(euler.sieve(10**6))

def iter_chain(n):
  while True:
    yield n
    if n == 0:
      return
    n = sum(euler.divisors(n, primes)) - n

def is_chain(n):
  seen = set()
  seenl = []
  for n in iter_chain(n):
    if n > 10**6:
      return (False, seenl)
    seenl.append(n)
    if n not in seen:
      seen.add(n)
    else:
      return (True, seenl)
  return (False, seenl)

ans = []
skip = set()
for i in range(2, 1000000):
  if i in skip:
    continue
  x, y = is_chain(i)
  if not x:
    skip.update(y)
  if x and y[0] == y[-1]:
    skip.update(y)
    if len(y) > len(ans):
      ans = y
print(min(ans))
