import euler
import itertools

n = 28123

def abundant():
  for i in range(1, n + 1):
    if euler.sum_of_divisors(i) - i > i:
      yield i

ab = list(abundant())
sumset = set()
for a in ab:
  for b in itertools.takewhile(lambda x: a + x <= n, ab):
    sumset.add(a + b)

ans = [i for i in range(1, n + 1) if i not in sumset]
print(sum(ans))
