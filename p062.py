import itertools

def cubes():
  for i in itertools.count(1):
    yield (i, "".join(sorted(str(i**3))))

cubemap = {}
for i, cube in cubes():
  cubemap.setdefault(cube, []).append(i)
  if len(cubemap[cube]) == 5:
    print(min(cubemap[cube]) ** 3)
    break
  
