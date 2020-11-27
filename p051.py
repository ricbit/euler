import euler
import itertools

M = 1000000
primes = list(euler.sieve(M))
primeset = set(primes)

def intmask(mask):
  ans = 0
  for d in mask:
    ans = ans * 10 + d
  return ans

def candidates(base, imask, limit):
  for d in range(10):
    n = base + d * imask
    if limit <= n < 10 * limit:
      yield n in primeset

def itermasks(p):
  d = euler.digits(p)
  limit = 10 ** (d - 1)
  allmasks = itertools.product(range(2), repeat=d)
  for mask in itertools.islice(allmasks, 1, 2 ** d - 1):
    base = int("".join((i if j == 0 else "0") for i,j in zip(str(p), mask)))
    imask = intmask(mask)
    yield (sum(candidates(base, imask, limit)), base, imask)

def search():
  start = primes.index(11)
  for p in itertools.islice(primes, start, len(primes)):
    c, base, imask = max(itermasks(p))
    if c >= 8:
      for d in range(10):
        pp = base + d * imask
        if pp in primeset:
          print(pp)
          return

search()

