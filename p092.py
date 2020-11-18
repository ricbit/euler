import math

def sumdigits(n):
  ans = 0
  while n > 0:
    ans += (n % 10) ** 2
    n //= 10
  return ans

def chain(n):
  while True:
    yield n    
    if n == 1 or n == 89:
      break
    n = sumdigits(n)

def last(it):
  for i in it:
    ans = i
  return ans

def split(n, start, current):
  if n == 0:
    yield current
    return 
  if start == 9:
    current.update({9: n})
    yield current
    return
  for i in range(n + 1):
    new = current.copy()
    if i > 0:
      new.update({start: i})
    yield from split(n - i, start + 1, new)

def multinomial(digits):
  ans = math.factorial(sum(digits.values()))
  ans //= math.prod(math.factorial(x) for x in digits.values())
  return ans

ans = 0 
for digits in split(7, 0, {}):
  n = sum(k * i * i for i, k in digits.items())
  if n > 0 and last(chain(n)) == 89:
    ans += multinomial(digits)
print(ans)
