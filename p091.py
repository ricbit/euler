def dist(x1, y1, x2, y2):
  return (x2 - x1) ** 2 + (y2 - y1) ** 2

M = 50
ans = set()
for x1 in range(M + 1):
  for x2 in range(x1, M + 1):
    starty = 1 if x1 == 0 else 0
    for y1 in range(starty, M + 1):
      for y2 in range(M + 1):
        a = dist(0, 0, x1, y1)
        b = dist(0, 0, x2, y2)
        c = dist(x1, y1, x2, y2)
        h = max(a, b, c)
        if 2 * h == a + b + c and min(a, b, c) > 0:
          t = [(x1, y1), (x2, y2)]
          t.sort()
          ans.add(tuple(t))
print(len(ans))
        
