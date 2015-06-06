maxAux [] a = a
maxAux (x:xs) a = if x > a then maxAux xs x else maxAux xs a

maxn (x:xs) = maxAux xs x

sacar [] a = []
sacar (x:xs) a = if x == a then xs else x:(sacar xs a)

sortword [] = []
sortword ls = (maxn ls) : (sortword (sacar ls (maxn ls)))

mapsort ls = map sortword (split ls) 

sort ls = juntar (mapsort ls)

juntar [] = []
juntar (x:xs) = x ++ (juntar xs)

split [] = []
split ls = fst (word ls) : split (snd (word ls))

word [] = ([],[])
word (x:xs) 
	|x == ' ' = ([x] , xs)
	|otherwise = (x : (fst (word xs)), snd (word xs))
