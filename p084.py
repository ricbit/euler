import random

path = """
GO A1 CC1 A2 T1 R1 B1 CH1 B2 B3
JAIL C1 U1 C2 C3 R2 D1 CC2 D2 D3
FP E1 CH2 E2 E3 R3 F1 F2 U2 F3 
G2J G1 G2 CC3 G3 R4 CH3 H1 T2 H2
""".strip().split()
rpath = {k:i for i, k in enumerate(path)}

ch_next = "GO JAIL C1 E3 H2 R1".split()
r_next = {"CH1": "R2", "CH2": "R3", "CH3": "R1"}
u_next = {"CH1": "U1", "CH2": "U2", "CH3": "U1"}

dice_size = 4

class Monopoly:
  def __init__(self):
    self.doubles = 0
    self.pos = 0
    self.visited = [0] * len(path)

  def update_cc(self):
    card = random.randint(0, 15)
    if card == 0:
      self.pos = rpath["GO"]
    elif card == 1:
      self.pos = rpath["JAIL"]

  def update_ch(self):
    card = random.randint(0, 15)
    if card < 6:
      self.pos = rpath[ch_next[card]]
    elif 6 <= card < 8:
      self.pos = rpath[r_next[path[self.pos]]]
    elif card == 8:
      self.pos = rpath[u_next[path[self.pos]]]
    elif card == 9:
      self.pos = (self.pos + len(path) - 3) % len(path)

  def next_pos(self, d1, d2):
    self.doubles = self.doubles + 1 if d1 == d2 else 0
    if self.doubles == 3:
      self.doubles = 0
      self.pos = rpath["JAIL"]
      return
    self.pos = (self.pos + d1 + d2) % len(path)
    if self.pos == rpath["G2J"]:
      self.pos = rpath["JAIL"]
      return
    if any(self.pos == rpath[cc] for cc in ["CC1", "CC2", "CC3"]):
      self.update_cc()
      return
    if any(self.pos == rpath[cc] for cc in ["CH1", "CH2", "CH3"]):
      self.update_ch()
      return

  def iter_pos(self):
    d1 = random.randint(1, dice_size)
    d2 = random.randint(1, dice_size)
    self.next_pos(d1, d2)
    self.visited[self.pos] += 1

  def run(self, size):
    self.size = size
    for i in range(size):
      self.iter_pos()

  def print_table(self):
    table = [(v, name) for v, name in zip(self.visited, path)]
    for v, name in sorted(table):
      print(name, v, "%.3f" % (v / self.size * 100))

  def print_modal(self):
    table = [(v, i) for i, v in enumerate(self.visited)]
    table.sort(reverse=True)
    modal = "".join("%02d" % table[i][1] for i in range(3))
    print(modal)

game = Monopoly()
game.run(30000000)
game.print_modal()
