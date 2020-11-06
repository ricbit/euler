ans = []
for a in range(100, 1000):
  for b in range(100, 1000):
    n = a * b
    s = str(n)
    if s == s[::-1]:
      ans.append(n)
print(max(ans))
      
      

