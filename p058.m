diag[n_] := Table[(2*n+1)^2 - 2 * i * n, {i, 0, 3}]
pdiag[n_] := Total[Boole[PrimeQ[diag[n]]]]
next[{i_, p_}] := {i + 1, p + pdiag[i + 1]}
check[{i_, p_}] := p / (1 + 4 i) > 10 / 100
{n, p} = NestWhile[next, next[{0, 0}], check]
Print[2 n + 1]
