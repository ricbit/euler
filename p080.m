squares = Table[i ^ 2, {i, 1, 100}]
nonsquares = Select[Range[100], Not[MemberQ[squares, #]]&]
sumdigits[k_] := Total[RealDigits[Sqrt[k], 10, 100][[1]]]
Print[Total[Map[sumdigits, nonsquares]]]
