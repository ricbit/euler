squares = Table[i ^ 2, {i, 1, 100}]
nonsquares = Select[Range[10000], Not[MemberQ[squares, #]]&]
len = Map[Length[ContinuedFraction[Sqrt[#]][[2]]]&, nonsquares]
Print[Length[Select[len, OddQ]]]
