def sumdigits(n):
  return sum(int(d)**5 for d in str(n))

ans = 0
for i in range(10, 1000000):
  if i == sumdigits(i):
    print(i, sumdigits(i))
    ans += i
print(ans)
  
