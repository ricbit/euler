M = 12000
bestrange[d_] := Range[Ceiling[d / 3], Floor[d / 2]]
redfrac[d_] := Length[Select[bestrange[d], GCD[#, d] == 1&]]
Print[Total[ParallelMap[redfrac, Range[2, M]]]]
