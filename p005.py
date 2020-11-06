import math

def prime(p):
  for i in range(2, math.floor(p**0.5) + 1):
    if p % i == 0:
      return False
  return True

primes = [i for i in range(2, 21) if prime(i)]
coef = [1] * len(primes)

def maxcoef(n, p):
  ans = 0
  while n % p == 0:
    ans += 1
    n /= p
  return ans

for i, p in enumerate(primes):
  for n in range(2, 20):
    coef[i] = max(coef[i], maxcoef(n, p))

ans = 1
for p, c in zip(primes, coef):
  ans *= p ** c

print(ans)

