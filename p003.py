import euler

def largest(n):
  current = n
  for i in range(2, n + 1):
    while current % i == 0:
      current //= i
    if (euler.is_prime(current)):
      return current

print(largest(600851475143))
