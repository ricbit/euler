twenty = """
one two three four five six seven eight nine ten
eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen twenty
""".split()
hundred = "ten twenty thirty forty fifty sixty seventy eighty ninety".split()

def number(n):
  if n == 1000:
    return "one thousand"
  if n <= 20:
    return twenty[n - 1]
  if n < 100:
    base = hundred[n // 10 - 1]
    if n % 10 > 0:
      base += "-" + twenty[n % 10 - 1]
    return base
  base = twenty[n // 100 - 1] + " hundred"
  if n % 100 > 0:
    base += " and " + number(n % 100)
  return base

def remove(n):
  return n.replace("-", "").replace(" ","")

print(sum(len(remove(number(i))) for i in range(1, 1001)))
