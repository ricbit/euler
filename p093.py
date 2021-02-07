import itertools
from fractions import Fraction as F

ops = [
  lambda a, b: a + b,
  lambda a, b: a - b,
  lambda a, b: b - a,
  lambda a, b: a * b,
  lambda a, b: a / b if b != 0 else 0,
  lambda a, b: b / a if a != 0 else 0
]

def count(digits):
  s = set()
  for op1, op2, op3 in itertools.product(ops, repeat=3):
    for d0, d1, d2, d3 in itertools.permutations(digits):
      s.add(op3(op1(d0, d1), op2(d2, d3)))
      s.add(op1(d0, op2(d1, op3(d2, d3))))
  for i in itertools.count(1):
    if i not in s:
      return i

def digits():
  for d in itertools.combinations([F(k, 1) for k in range(10)], 4):
    yield (count(d), d)

print(max(digits()))
  
