mat = [[int(i) for i in line.split(",")] for line in open("p081_matrix.txt").readlines()]
ans = [[0] * 80 for i in range(80)]

for x in range(79, -1, -1):
  for y in range(79, -1, -1):
    if x == 79:
      if y == 79:
        ans[x][y] = mat[x][y]
      else:
        ans[x][y] = mat[x][y] + ans[x][y + 1]
    else:
      if y == 79:
        ans[x][y] = mat[x][y] + ans[x + 1][y]
      else:
        ans[x][y] = min(mat[x][y] + ans[x + 1][y], mat[x][y] + ans[x][y + 1])
print(ans[0][0])
