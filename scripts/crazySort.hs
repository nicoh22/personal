crazySort [] = []
crazySort (x : xs) = x : (crazySort (reverse xs) )

suma2 [] = []
suma2 (x:xs) = if xs == [] then [x] 
               else ( x + (head xs) ) : suma2(tail xs)

casiGauss ls = suma2 (crazySort ls)


gauss [] = 0
gauss ls = if length ls `mod` 2 == 0 then 
               (length (casiGauss ls)) * (head (casiGauss ls)) 
           else 
               (length (casiGauss ls) - 1) * (head (casiGauss ls) ) + (head(casiGauss ls) `div` 2)
