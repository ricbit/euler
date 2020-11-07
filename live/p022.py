unparsed = open("p022_names.txt", "rt").read().split(",")
parsed = [name[1:-1] for name in unparsed]
ans = 0
for i, name in enumerate(sorted(parsed)):
  number = sum(ord(c) - ord('A') + 1 for c in name)
  ans += number * (i + 1)
print(ans)
