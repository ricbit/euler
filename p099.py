import math

def numbers():
  for i, line in enumerate(open("p099_base_exp.txt", "rt").readlines()):
    a, b = map(int, line.split(","))
    yield (b * math.log(a), i + 1)

print(max(numbers()))    
