import math

def prime(p):
  for i in range(2, math.floor(p**0.5) + 1):
    if p % i == 0:
      return False
  return True

def largest(n):
  current = n
  for i in range(2, n):
    if current % i == 0:
      while current % i == 0:
        current //= i
    if (prime(current)):
      return current

print(largest(600851475143))
