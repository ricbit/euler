import math

def rects(a, b):
  return a*b*(1+a+b+a*b)//4

def invert(a, c):
  return (((a+a*a+16*c)/(a*(1+a)))**0.5-1) / 2

M = 2000000

def trials():
  for i in range(1, int(M**0.5)):
    bb = invert(i, M)
    for b in range(math.floor(bb), math.ceil(bb) + 1):
      r = rects(i, b)
      yield ((r - M)**2, (i, b), i*b)

print(min(trials()))
  

