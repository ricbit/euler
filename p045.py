def triangle(n):
  return n * (n + 1) // 2

def pentagonal(n):
  return n * (3 * n - 1) // 2

def hexagonal(n):
  return n * (2 * n - 1)

n = 100000

t = set(triangle(i) for i in range(n))
p = set(pentagonal(i) for i in range(n))
h = set(hexagonal(i) for i in range(n))

print(t.intersection(p).intersection(h))
