import euler
import itertools

print(sum(itertools.takewhile(lambda x: x < 2000000, euler.primes())))
