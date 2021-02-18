mat = [[int(i) for i in line.split(",")] for line in open("p082_matrix.txt").readlines()]
N = 80
ans = [[0] * N for i in range(N)]

for y in range(N):
  ans[y][N - 1] = mat[y][N - 1]

for x in range(N - 2, -1, -1):
  for yenter in range(N):
    best = 1e30
    for yexit in range(N):
      partial = ans[yexit][x + 1]
      for k in range(min(yenter, yexit), max(yenter, yexit) + 1):
        partial += mat[k][x]
      if partial < best:
        best = partial
    ans[yenter][x] = best
      
print(min(ans[y][0] for y in range(N)))        

