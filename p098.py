import itertools
import euler

all_words = [x.strip('"') for x in open("p098_words.txt", "rt").read().split(",")]
anagrams = {}
for word in all_words:
  anagrams.setdefault("".join(sorted(list(word))), []).append(word)

def iter_anagrams():
  for a, b in anagrams.items():
    if len(b) > 1:
      yield (a, b)

biggest = 0
for a, b in iter_anagrams():
  biggest = max(biggest, len(a))

squares = {}
for i in itertools.count(1):
  if i * i > 10 ** biggest:
    break
  s = str(i*i)
  squares.setdefault(len(s), []).append(s)

def iter_pairs():
  for a, b in iter_anagrams():
    for x, y in itertools.combinations(b, 2):
      yield x, y

def match(word, square):
  m = {}
  values = set()
  for c, d in zip(word, square):
    m.setdefault(c, set()).add(d)
    values.add(d)
    if len(m[c]) > 1:
      return {}
  if len(values) != len(m.keys()):
    return {}
  return m

def also_square(word, m):
  n = "".join(euler.first(m[c]) for c in word)
  if n in squares[len(word)]:
    return n
  else:
    return 0

ans = 0
for a, b in iter_pairs():
  for asquare in squares[len(a)]:
    match_dict = match(a, asquare)
    if match_dict:
      bsquare = also_square(b, match_dict)
      if bsquare:
        ans = max(ans, int(asquare), int(bsquare))
print(ans)




