-- Inciso a 

entrelazar::[a]->[a]->[a]
entrelazar xs ys = concat(zipWith (\x y -> x:y:[]) xs ys)

-- Probado empiricamente que funciona con infinitas, pero ni idea porque.

-- Inciso b

duplicarApariciones::[a]->[a]
duplicarApariciones as = entrelazar as as

-- Inciso c
dynprog::([a]->a)->a->Int->[a]
dynprog _ x 0 = [x]
dynprog f x n | n > 0 = (f rec):rec
                          where rec = dynprog f x (n-1)

factorial = dynprog f 1 
              where f = (\res -> (head res) * (1 + length res ))

-- Inciso d
fibonacci :: Int -> [Int]
fibonacci = dynprog f 1
                where f = (\res -> if (length res) == 1 then 1 else head(res) + head(tail(res)))
