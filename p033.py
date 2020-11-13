import math
from fractions import Fraction as F

# ab / cd  = a/d
# ab / cd  = b/c
# ab / cd  = b/d
# ab / cd  = a/c

def fractions():
    for num in range(10, 100):
      for den in range(num + 1, 100):
        a = num // 10
        b = num % 10
        c = den // 10
        d = den % 10

        if d == 0 and b == 0:
          continue

        if b == c and d != 0 and F(a, d) == F(num, den):
          yield F(a, d)

        if a == d and c != 0 and F(b, c) == F(num, den):
          yield F(b, c)

        if a == c and d != 0 and F(b, d) == F(num, den):
          yield F(b, d)

        if b == d and c != 0 and F(a, c) == F(num, den):
          yield F(a, c)

p = math.prod(fractions())
print(p.denominator)
