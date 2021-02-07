x = Max[Table[n / EulerPhi[n], {n, 2, 1000000}]]
Print[Select[Range[1000000], # / EulerPhi[#] == x &]]
