import math

def penta(n):
  return n * (3 * n - 1) // 2

def ispenta(x):
  d = 24 * x + 1
  n = math.isqrt(d)
  if n * n != d:
    return False
  return (n + 1) % 6 == 0

def solutions():
  for i in range(1, 5000):
    for j in range(i + 1, 5000):
      a = penta(i)
      b = penta(j)
      if ispenta(a + b) and ispenta(b - a):
        yield (b - a, a, b, a + b)

print(min(solutions()))        

