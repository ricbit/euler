next[n_] := DivisorSigma[1, n] - n
cycle[n_] := NestWhileList[next[#]&, n, (next[#] != n) && (1 < next[#] < 1000000) &]
Print[Table[cycle[k], {k,1,30}]]
