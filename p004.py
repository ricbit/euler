import itertools

def combinations():
  for a, b in itertools.combinations_with_replacement(range(100, 1000), 2):
    n = a * b
    s = str(n)
    if s == s[::-1]:
      yield n

print(max(combinations()))
      
      

