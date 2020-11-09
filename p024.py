import itertools
import euler

digits = list(range(10))
perm = itertools.permutations(digits)
print("".join(str(i) for i in euler.first(itertools.islice(perm, 10 ** 6 - 1, 10 ** 6))))

