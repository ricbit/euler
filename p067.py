given = open("p067_triangle.txt", "rt").readlines()
mat = [[int(i) for i in line.split()] for line in given]
n = len(mat)
ans = [[0] * n for i in range(n)]

for x in range(n):
  ans[n - 1][x] = mat[n - 1][x]

for y in range(n - 2, -1, -1):
  for x in range(y + 1):
    ans[y][x] = mat[y][x] + max(ans[y + 1][x], ans[y + 1][x + 1])

print(ans[0][0])

