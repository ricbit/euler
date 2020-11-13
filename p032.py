import math
import itertools

numbers = set()
for digits in itertools.permutations(list(range(1, 10))):
  for times in range(1, 7 + 1):
    for equal in range(times + 1, 9):    
      a = int("".join(str(i) for i in digits[:times]))
      b = int("".join(str(i) for i in digits[times:equal]))
      c = int("".join(str(i) for i in digits[equal:]))
      if a * b == c:       
        numbers.add(c)
print(sum(numbers))
