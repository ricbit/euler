import datetime

ans = 0
for year in range(1901, 2001):
  for month in range(1, 13):
    date = datetime.date(year, month, 1)
    if date.weekday() == 6:
      ans += 1
print(ans)
