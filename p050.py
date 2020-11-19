import euler
import itertools

n = 10**6

primes = list(itertools.takewhile(lambda x: x < n, euler.primes()))
primeset = set(primes)

def findsums():
  for i in range(len(primes)):
    acc = 0
    for j in range(i, len(primes)):
      if acc + primes[j] < n:
        acc += primes[j]
        if acc in primeset:
          yield j - i, acc
      else:
        break

print(max(findsums()))          


