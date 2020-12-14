import euler
import itertools

primes = list(euler.sieve(200))

def custom_partitions(n, elements, sol=[], index=0):
  if index >= len(elements):
    return
  for i in itertools.count(0):
    k = i * elements[index]
    if k > n:
      return
    next_sol = sol + [elements[index]] * i
    if k == n:
      yield next_sol
      return
    yield from custom_partitions(n - k, elements, next_sol, index + 1)

comp = lambda x: len(list(custom_partitions(x, primes))) < 5000 
print(euler.first(itertools.dropwhile(comp, itertools.count(2))))
