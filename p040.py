import math

fracs = []
current = 1

while len(fracs) <= 10**6:
  fracs += [int(i) for i in str(current)]
  current += 1

print(math.prod(fracs[10**i - 1] for i in range(7)))
