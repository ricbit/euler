import itertools
from collections import Counter

text = list(map(int, open("p059_cipher.txt", "rt").read().split(",")))
expected = "".join(sorted(list("etaoinshr")))

def decode(text, key):
  hist = Counter()
  for a, b in zip(text, itertools.cycle(key)):
    c = chr(a ^ b).lower()
    if "a" <= c <= "z":
      hist[c] += 1
  linhist = [(f, c) for c, f in hist.items()]
  linhist.sort(reverse=True)
  return linhist[:len(expected)]

def ans(text, key):
  return sum(a ^ b for a, b in zip(text, itertools.cycle(key)))

a = ord('a')
z = ord('z')
for key in itertools.permutations(range(a, z + 1), 3):
  hist = decode(text, key)
  actual = "".join(sorted(x[1] for x in hist))
  if actual == expected:
    print(ans(text, key))
