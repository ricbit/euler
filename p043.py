import itertools

primes = [17, 13, 11, 7, 5, 3, 2]
digits = set(str(i) for i in range(10))

def search(seed, digits, i):
  if i == 7:
    yield int("".join(seed))
    return
  if int("".join(seed[:3])) % primes[i] != 0:
    return
  for d in digits:
    yield from search([d] + seed, digits.difference(set([d])), i + 1)

def search_all():
  for seed in itertools.permutations(digits, 3):
    yield from search(list(seed), digits.difference(set(seed)), 0)

print(sum(search_all()))

