import euler

def digits():
  for a in range(1, 100):
    for b in range(1, 100):
      yield euler.sumdigits(a ** b)

print(max(digits()))

