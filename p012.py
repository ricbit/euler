import euler
import itertools

def triangle():
  t = 0
  for i in itertools.count(1):
    t += i
    yield t

bigger = itertools.dropwhile(lambda x: euler.number_of_divisors(x) < 500, triangle())
print(list(itertools.islice(bigger, 0, 1)))

