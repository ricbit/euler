import itertools

def triangle(n):
  return n * (n + 1) // 2

def square(n):
  return n * n

def pentagonal(n):
  return n * (3 * n - 1) // 2

def hexagonal(n):
  return n * (2 * n - 1)

def heptagonal(n):
  return n * (5 * n - 3) // 2

def octogonal(n):
  return n * (3 * n - 2)

functions = [triangle, square, pentagonal, hexagonal, heptagonal, octogonal]

def exactlyfour(func):
  figurates = (func(i) for i in itertools.count(1))
  four_or_less = itertools.takewhile(lambda x: x < 10000, figurates)
  return itertools.dropwhile(lambda x: x < 1000, four_or_less)

figurates = [list(exactlyfour(func)) for func in functions]
figmap = [{} for f in functions]
for fig, m in zip(figurates, figmap):
  for n in fig:
    prefix = n // 100
    m.setdefault(prefix, []).append(n)

def recsearch(level, prefix, ans):
  if len(ans) == 6:
    yield ans
    return
  for func in range(6):
    if func not in level:
      for n in figmap[func].get(prefix, []):
        if n not in ans:
          yield from recsearch(level.union([func]), n % 100, ans + [n])

def search():
  for n in figurates[5]:
    for candidate in recsearch(set([5]), n % 100, [n]):
      if candidate[0] // 100 == candidate[-1] % 100:
        yield candidate

print(list(sum(s) for s in search()))
  


