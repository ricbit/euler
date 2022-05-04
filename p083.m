file = ReadList["p083_matrix.txt", Record, RecordSeparators -> {"\n", ","}]
mat = Partition[file, 80]
neigh[y_, x_, n_] := {
    {y + 1, x, n}, {y - 1, x, n}, {y, x + 1, n}, {y, x - 1, n}}
validneigh[y_, x_, n_] := Select[
    neigh[y, x, n], 0 <= #[[1]] < n && 0 <= #[[2]] < n &]
fromindex[i_, n_] := {Floor[(i-1)/n], Mod[i+n-1,n], n}
toindex[y_, x_, n_] := y * n + x + 1
matyx[{y_, x_, n_}] := ToExpression[mat[[1+y]][[1+x]]]
mindex[i_, n_] := matyx[fromindex[i, n]]
edge[i_, {y_, x_, n_}] := i -> toindex[y, x, n]
indexneigh[i_, n_] := Map[{edge[i, #], mindex[i, n]}&, 
    Apply[validneigh, fromindex[i, n]]]
graph[n_] := With[{edgelist=Flatten[Table[indexneigh[i, n], {i, 1, n^2}], 1]},
    Graph[Map[#[[1]]&, edgelist], EdgeWeight->Map[#[[2]]&, edgelist]]]
shortest[n_] := FindShortestPath[graph[n], 1, n^2]
sumpath[n_] := Total[Map[matyx[fromindex[#, n]]&, shortest[n]]]
Print[sumpath[80]]

