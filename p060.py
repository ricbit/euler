import euler
import math
import sys

N = 100000000

primes = list(euler.sieve(N))
primeset = set(primes)

def concat(p1, p2):
  pa = int(str(p1) + str(p2))
  pb = int(str(p2) + str(p1))
  return pa in primeset and pb in primeset

trie = [False, {}]
for p in primes:
  t = trie
  for c in map(int, str(p)):
    t = t[1].setdefault(c, [False, {}])
  t[0] = True

def iterprimes(trie, n=0):
  if trie[0]:
    yield (n, trie)
  for digit, ntrie in trie[1].items():
    yield from iterprimes(ntrie, n * 10 + digit)

def genpairs():
  pairs = {}
  for p1, subtrie in iterprimes(trie):
    for p2, _ in iterprimes(subtrie):
      if p2 in primeset and concat(p1, p2):
        pairs.setdefault(tuple([p1]), set()).add(p2)
        pairs.setdefault(tuple([p2]), set()).add(p1)
  return pairs

stack = [{} for i in range(6)]
stack[2] = genpairs()

for n in range(3, 6):
  for p1, plist in stack[n - 1].items():
    for p2 in plist:
      p = list(p1) + [p2]
      p.sort()
      s = set(plist).intersection(set(stack[2][tuple([p2])]))
      if len(s) >= 6 - n:
        stack[n][tuple(p)] = s

for k, v in stack[5].items():
  print(k, v, sum(list(k) + list(v))) 
