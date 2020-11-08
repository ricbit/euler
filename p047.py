import euler
import itertools

n = 4

for i in itertools.count(2):
  if all(n == len(list(euler.factor(i + j))) for j in range(n)):
    print(i)
    break
