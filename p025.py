import euler
import itertools

fibs = itertools.dropwhile(lambda x: len(str(x[1])) < 1000, enumerate(euler.fibonacci()))
print(euler.first(fibs)[0] + 1)
