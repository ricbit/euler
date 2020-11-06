import euler
import itertools

fib = itertools.takewhile(lambda f: f < 4000000, euler.fibonacci())
print(sum(i for i in fib if i % 2 == 0))

