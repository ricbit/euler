import itertools

def count(n):
  for i in range(1, 10):
    if len(str(i ** n)) == n:
      yield (i ** n)

total = itertools.chain.from_iterable(count(i) for i in range(1, 22))    
print(len(list(total)))
