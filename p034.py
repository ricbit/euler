import math

ans = 0
for i in range(3, 100000):
  if sum(math.factorial(int(d)) for d in str(i)) == i:
    ans += i
print(ans)
  
