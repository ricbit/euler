from fractions import Fraction as F

goal = F(3, 7)
cur = F(0, 1)
for i in range(2, 1000000):
  f = F((i * goal.numerator) // goal.denominator, i)
  if f > cur and f < goal:
    cur = f
print(cur)
