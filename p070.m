check[n_] := Sort[IntegerDigits[n]] == Sort[IntegerDigits[EulerPhi[n]]]
cand = Select[Range[2, 9999999], check]
x = Min[Map[# / EulerPhi[#]&, cand]]
Print[Select[cand, # / EulerPhi[#] == x &]]
