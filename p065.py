import itertools
import fractions

F = fractions.Fraction

def coefs():
  yield from [2, 1, 2]
  for i in itertools.count(4, 2):
    yield from [1, 1, i]

def inverse(n):
  if n == F(0, 1):
    return F(0, 1)
  else:
    return F(1, 1) / n

n = 100
ans = 0
for c in itertools.islice(coefs(), 0, n):
  ans = F(c, 1) + inverse(ans)
print(sum(int(i) for i in str(ans.numerator)))


