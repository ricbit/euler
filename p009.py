def triples():
  for a in range(1, 1001):
    for b in range(a + 1, (1000 - a) // 2):
      yield (a, b, 1000 - a - b)

for a, b, c in triples():
  if a * a + b * b == c * c:
    print(a * b * c)
