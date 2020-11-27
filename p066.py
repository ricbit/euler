import math
import decimal
import itertools

def squarecoefs(D):
  c = decimal.Decimal(D).sqrt()
  while True:
    i = c.to_integral(decimal.ROUND_FLOOR)
    yield int(i)
    if c != i:
      c = decimal.Decimal(1) / (c - i)

def convergents(coefs):
  h0 = 0
  k0 = 1
  h1 = 1
  k1 = 0
  for a in coefs:
    hn = a * h1 + h0
    kn = a * k1 + k0
    yield (hn, kn)
    h0, k0, h1, k1 = h1, k1, hn, kn

def pell(D):
  for h, k in convergents(squarecoefs(D)):
    if h * h - D * k * k == 1:
      return h, k

def minimal():
  squares = set(i * i for i in range(100))
  for i in range(2, 1001):
    if i not in squares:
      h, k = pell(i)
      print(h, i)
      yield h, i

decimal.getcontext().prec = 300
print(max(minimal()))
