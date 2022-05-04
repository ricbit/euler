import itertools
import euler

primes = list(euler.sieve(n = 10 ** 6))

def search(k, sol):
  if k == 1:
    yield sol
  else:
    divs = list(sorted(euler.divisors(k, primes), reverse=True))
    for div in divs:
      if div > 1:
        yield from list(search(k // div, sol + [div]))

def mult_partitions(n):
  return set(tuple(sorted(p)) for p in search(n, []))

LIMIT = 13000
sizes = [10 ** 9] * 12001
for prod in range(2, LIMIT):
  for part in mult_partitions(prod):
    s = sum(part)
    size = len(part) + prod - s
    if size < len(sizes):
      sizes[size] = min(prod, sizes[size])

minps = set(x for i, x in enumerate(itertools.islice(sizes, 2, 12001)))
print(sum(minps))

