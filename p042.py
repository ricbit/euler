words = [word[1:-1] for word in open("p042_words.txt", "rt").read().split(",")]
triangle = set(n * (n + 1) // 2 for n in range(1, 1000))

ans = 0
for word in words:
  code = sum(ord(c) - ord('A') + 1 for c in word)
  if code in triangle:
    ans += 1
print(ans)

  
