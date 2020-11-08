import itertools

ans = set()
for a, b in itertools.product(range(2, 101), repeat=2):
  ans.add(a ** b)
print(len(ans))
