import euler

amicable = set()
for a in range(2, 10000):
  if a in amicable:
    continue
  b = euler.sum_of_divisors(a) - a
  if b > 1 and a != b and euler.sum_of_divisors(b) - b == a:
    amicable.add(a)
    amicable.add(b)

print(sum(amicable))
