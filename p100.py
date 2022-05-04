import math

x1, y1 = 3, 1
x, y = x1, y1
b = 0
while y + b < 10 ** 12:
  xk, yk = x1 * x + 8 * y1 * y, x1 * y + y1 * x
  x, y = xk, yk
  b = (1 + 2 * y + math.isqrt(1 + 8 * y * y)) // 2
print(b)
  
