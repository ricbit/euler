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
    g = math.gcd(hn, kn)
    hn //= g
    kn //= g
    yield (hn, kn)
    h0, k0, h1, k1 = h1, k1, hn, kn

decimal.getcontext().prec = 3000
ans = 0
for h, k in itertools.islice(convergents(squarecoefs(2)), 1001):
  if len(str(h)) > len(str(k)):
    ans += 1
print(ans)    
