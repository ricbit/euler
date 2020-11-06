import math

def prime(p):
  for i in range(2, math.floor(p**0.5) + 1):
    if p % i == 0:
      return False
  return True

primes = [2]

# p_n = n * ln n + n * ln ln n + 

while len(primes) < 10001:
  pa = primes[-1] + 1
  while not prime(pa):
    pa += 1
  primes.append(pa)

print(primes[-1])
