n = 1001
mat = [[0] * n for i in range(n)]
x = y = n // 2
mat[y][x] = 1
directions = [(1, 0), (0, -1), (-1, 0), (0, 1)]
current = 1
for side in range(2, 1 + n, 2):
  x += 1
  current += 1
  mat[y][x] = current
  moves = [side] * 4
  moves[0] -= 1
  for d, steps in zip(directions, moves):
    for step in range(steps):
      y += d[0]
      x += d[1]
      current += 1
      mat[y][x] = current
ans = 0
for i in range(n):
  ans += mat[i][i]
  ans += mat[n - 1 - i][i]
ans -= mat[n // 2][n // 2]
print(ans)

