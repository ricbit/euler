import euler
import itertools

#print(sum(itertools.takewhile(lambda x: x < 2000000, euler.primes())))

# Lucy Hedgehog with square root trick
def sum_primes(n):
    r = int(n**0.5)
    V = sorted(set([n//i for i in range(1, r+1)] + list(range(1, r+1))))
    S = {v: v*(v+1)//2 - 1 for v in V}  # initial values of S(v, 1)

    for p in range(2, r+1):
        if S[p] > S[p - 1]:  # prime detection
            sp = S[p - 1]
            p2 = p * p
            for v in reversed(V):
                if v < p2:
                    break
                S[v] -= p * (S[v // p] - sp)

    return S[n]

print(sum_primes(2000000))
