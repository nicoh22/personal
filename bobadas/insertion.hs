maxAux [] a = a
maxAux (x:xs) a = if x > a then maxAux xs x else maxAux xs a

maxn (x:xs) = maxAux xs x

sacar [] a = []
sacar (x:xs) a = if x == a then xs else x:(sacar xs a)

sort [] = []
sort ls = (maxn ls) : (sort (sacar ls (maxn ls)))

 
