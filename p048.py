m = 10**10

print(sum(pow(i, i, m) for i in range(1, 1001)) % m)
