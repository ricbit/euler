import euler
import itertools

best = 0
for n in range(2, 10):
  for p in itertools.permutations(list(range(1, n + 1))):
    s = int("".join(str(i) for i in p))
    if euler.is_prime(s):
      best = s
print(best)
