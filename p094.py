import itertools
import math

def pell(x1, y1, D):
  xk1, yk1 = x1, y1
  while True:
    yield (xk1, yk1)
    xk = x1 * xk1 + D * y1 * yk1
    yk = xk1 * y1 + x1 * yk1
    xk1, yk1 = xk, yk

def heron(a, b, c):
  s = (a + b + c) // 2
  x = s * (s - a) * (s - b) * (s - c)
  return math.isqrt(x) ** 2 == x and x > 0

def sides(offset):
  for x, y in pell(2, 1, 3):
    n = 4 + 3 * (2 * y) ** 2
    a = (math.isqrt(4 + 3 * (2 * y) ** 2) + offset) // 3  
    if heron(a, a, a + offset):
      yield 3 * a + offset

ans = sum(itertools.takewhile(lambda x: x < 10**9, sides(-1)))
ans += sum(itertools.takewhile(lambda x: x < 10**9, sides(1)))
print(ans)
