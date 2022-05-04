import math
import itertools
import sys
import bisect

squares = set(i * i for i in range(100000))

def works(i, j, k):
  d1 = (i + j) ** 2 + k ** 2
  d2 = (i + k) ** 2 + j ** 2
  d3 = (k + j) ** 2 + i ** 2
  if d1 in squares and d1 <= d2 and d1 <= d3:
    return True, d1, d2, d3
  if d2 in squares and d2 <= d1 and d2 <= d3:
    return True, d1, d2, d3
  if d3 in squares and d3 <= d2 and d3 <= d1:
    return True, d1, d2, d3
  return False, 0, 0, 0

def naive(M):
  count = 0
  for i in range(1, M):
    for j in range(1, i + 1):
      for k in range(1, j + 1):
        if (a := works(i, j, k))[0]:
          _, d1, d2, d3 = a
          count += 1
  return count

def primitive_triples(size_max):
  for m in range(1, size_max):
    for n in range(1 + m % 2, m, 2):
      if math.gcd(m, n) == 1:
        yield m ** 2 - n ** 2, 2 * m * n, m ** 2 + n ** 2

def all_triples(size_max):
  for a, b, c in primitive_triples(size_max):
    for k in itertools.count(1):
      aa, bb, cc = a * k, b * k, c * k
      if aa >= size_max or bb >= size_max or cc >= size_max:
        break
      yield aa, bb, cc

def split_single(size_max, al, bl):
  for pa in range(1, al // 2 + 1):
    aa, bb, cc = pa, al - pa, bl
    if aa < size_max and bb < size_max and cc < size_max:
      good, d1, d2, d3 = works(aa, bb, cc)
      if good:
        yield tuple(sorted([aa, bb, cc]))

def split_triple(size_max):
  for a, b, c in all_triples(3 * size_max + 1):
    yield from split_single(size_max, a, b)
    yield from split_single(size_max, b, a)

def count_solutions(size_max):
  print("trying ", size_max)
  return len(set(split_triple(size_max)))

GOAL = 1000000
ans = bisect.bisect(list(range(4000)), GOAL, key=count_solutions)
print(ans - 1)
  
