from collections import Counter

values = {
  '2': 2,
  '3': 3,
  '4': 4,
  '5': 5,
  '6': 6,
  '7': 7,
  '8': 8,
  '9': 9,
  'T': 10,
  'J': 11,
  'Q': 12,
  'K': 13,
  'A': 14
}

def parse_hand(cards):
  hand = []
  for rank, suit in cards:
    hand.append((values[rank], suit))
  return list(sorted(hand))

def discarded(hand, skips):
  return skips + [rank for rank, suit in reversed(hand) if rank not in skips]

def high_card(hand):
  return True, discarded(hand, [])

def count_ranks(hand):
  c = Counter()
  for rank, suit in hand:
    c[rank] += 1
  return c

def count_suits(hand):
  c = Counter()
  for rank, suit in hand:
    c[suit] += 1
  return c

def one_pair(hand):
  c = count_ranks(hand)
  upper = max(c.values())
  if upper != 2:
    return False, []
  ranks = [k for k, v in c.items() if v == 2]
  if len(ranks) > 1:
    return False, []
  return True, discarded(hand, [ranks[0]])

def two_pairs(hand):
  c = count_ranks(hand)
  upper = max(c.values())
  if upper != 2:
    return False, []
  ranks = [k for k, v in c.items() if v == 2]
  if len(ranks) != 2:
    return False, []
  maxrank, minrank = ranks
  return True, discarded(hand, [maxrank, minrank])

def three_of_a_kind(hand):
  c = count_ranks(hand)
  upper = max(c.values())
  if upper != 3:
    return False, []
  if 2 in c.values():
    return False, []
  ranks = [k for k, v in c.items() if v == 3]
  return True, discarded(hand, ranks)

def full_house(hand):
  c = count_ranks(hand)
  if 3 not in c.values() or 2 not in c.values():
    return False, []
  big = [k for k, v in c.items() if v == 3]
  small = [k for k, v in c.items() if v == 2]
  return True, discarded(hand, [big[0], small[0]])

def consecutive(hand):
  ranks = [rank for rank, suit in hand]
  return all(a == b - 1 for a, b in zip(ranks, ranks[1:]))

def straight(hand):
  if not consecutive(hand):
    return False, []
  return True, discarded(hand, [rank for rank, suit in reversed(hand)])

def flush(hand):
  c = count_suits(hand)
  if 5 not in c.values():
    return False, []
  return True, discarded(hand, [rank for rank, suit in reversed(hand)])

def straight_flush(hand):
  if not consecutive(hand):
    return False, []
  c = count_suits(hand)
  if 5 not in c.values():
    return False, []
  return True, discarded(hand, [rank for rank, suit in reversed(hand)])

def royal_flush(hand):
  if not consecutive(hand):
    return False, []
  c = count_suits(hand)
  if 5 not in c.values():
    return False, []
  if hand[0] != 10:
    return False, []
  return True, discarded(hand, [rank for rank, suit in reversed(hand)])

def four_of_a_kind(hand):
  c = count_ranks(hand)
  upper = max(c.values())
  if upper != 4:
    return False, []
  ranks = [k for k, v in c.items() if v == 4]
  return True, discarded(hand, ranks)

scores = [
  ("royal flush", royal_flush),
  ("straight flush", straight_flush),
  ("four of a kind", four_of_a_kind),
  ("full house", full_house),
  ("flush", flush),
  ("straight", straight),
  ("three of a kind", three_of_a_kind),
  ("two pairs", two_pairs),
  ("one pair", one_pair),
  ("high card", high_card)
]

def best_score(hand):
  for i, (name, score) in enumerate(scores):
    result, value = score(hand)
    if result:
      return len(scores) - i, name, value
  return "none", 0 

hands = []
for line in open("p054_poker.txt", "rt"):
  s = line.strip().split()
  hands.append((parse_hand(s[0:5]), parse_hand(s[5:])))

def winner(p1, p2):
  s1, n1, v1 = best_score(p1)
  s2, n2, v2 = best_score(p2)
  if (s1, v1) > (s2, v2):
    return 1
  else:
    return 2

p1wins = 0
for p1, p2 in hands:
  if winner(p1, p2) == 1:
    p1wins += 1

print(p1wins)

