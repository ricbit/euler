import math
import euler
import itertools

goal = list(str(i) for i in range(1, 10))

def search(n):
  for i in itertools.count(1):
    d = euler.digits(i)
    if d * n > 9:
      return
    s = "".join(str(i * j) for j in range(1, n + 1))
    if list(sorted(s)) == goal:
      yield s

def best():
  for n in range(2, 10):
    yield from search(n)

print(max(best()))
  
