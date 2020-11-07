def period(n):
  a = 1
  pos = 0
  remainder = {1: 0}
  while True:
    pos += 1
    if a == 0:
      return 0
    r = a * 10 % n
    if r in remainder:
      return pos - remainder[r]
    remainder[r] = pos
    a = r

cycles = [(period(i), i) for i in range(2, 1000)]
print(max(cycles)[1])

    
