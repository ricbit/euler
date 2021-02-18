import itertools

ring = [[1, 2, 3], [4, 3, 5], [6, 5, 7], [8, 7, 9], [10, 9, 2]]

def getsum(p, r):
  return sum(p[i-1] for i in r)

def getstring(p, r):
  return "".join(str(p[i - 1]) for i in r)

def unique(p):
  t = [p[r[0] - 1] for r in ring]
  q = ["".join(str(p[i - 1]) for i in r) for r in ring]
  m = min(t)
  i = t.index(m)
  return "".join(q[(i + j) % len(ring)] for j in range(len(ring)))

ans = set()
for x in itertools.permutations(range(1, 11)):
  p = list(x)
  s = getsum(p, ring[0])
  if all(getsum(p, r) == s for r in ring):
    u = unique(p)
    if len(u) == 16:
      ans.add(unique(p))
print(max(ans))
  
