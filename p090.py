import itertools

squares = [list(map(int, ("0"+str(i * i))[-2:])) for i in range(1, 10)]

def hassquare(dice1, dice2, sq):
  return (
    (sq[0] in dice1 and sq[1] in dice2) or 
    (sq[0] in dice2 and sq[1] in dice1))

def valid(dice1, dice2):
  if 6 in dice1 or 9 in dice1:
    dice1.update([6, 9])
  if 6 in dice2 or 9 in dice2:
    dice2.update([6, 9])
  return all(hassquare(dice1, dice2, sq) for sq in squares)

ans = set()
for dice1 in itertools.combinations(range(10), 6):
  for dice2 in itertools.combinations(range(10), 6):
    if valid(set(dice1), set(dice2)):
      x = [tuple(sorted(dice1)), tuple(sorted(dice2))]
      x.sort()
      ans.add(tuple(x))
print(len(ans))

