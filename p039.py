
def count(n):
  for a in range(1, n // 3 + 1):
    for b in range(a + 1, n - a):
      if a**2 + b**2 == (n - a - b)**2:
        yield 1

print(max((sum(count(i)), i) for i in range(1, 1001)))
