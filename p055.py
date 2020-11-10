def palin(x):
  return str(x) == str(x)[::-1]

def lychrel(x):
  for i in range(50):
    b = int(str(x)[::-1])
    if palin(x + b):
      return False
    x += b
  return True

ans = 0
for i in range(1, 10000):
  if lychrel(i):
    ans += 1
print(ans)
  
