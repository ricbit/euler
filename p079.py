guess="73162890" # by hand
pwd = [x.strip() for x in open("p079_keylog.txt", "rt").readlines()]

def search():
  for p1, p2, p3 in pwd:
   if not(guess.index(p1) < guess.index(p2) < guess.index(p3)):
      return "fail"
  return "pass"

print(guess, search())
