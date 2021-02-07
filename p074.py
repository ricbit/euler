import math

def sumfac(n):
  ans = 0
  while n:
    ans += math.factorial(n % 10)
    n //= 10
  return ans

def chain(n):
  s = set()
  while n not in s:
    s.add(n)
    n = sumfac(n)
  return len(s)

total = 0
for i in range(1000000):
  if chain(i) == 60:
    total += 1
print(total)
    
