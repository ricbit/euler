ans = 0
for i in range(1, 10**6):
  if i % 10 == 0 or i % 2 == 0:
    continue
  decimal = str(i)
  binary = bin(i)[2:]
  if decimal == decimal[::-1] and binary == binary[::-1]:
    ans += i
    
print(ans)
