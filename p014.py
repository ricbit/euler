import euler
import itertools

chains = ((len(list(euler.collatz_path(i))), i) for i in range(1, 1000000))
print(max(chains)[1])
