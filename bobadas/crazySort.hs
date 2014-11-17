crazySort [] = []
crazySort (x : xs) = x : (crazySort (reverse xs) )

casiGauss [] = []
casiGauss (x:xs) = if xs == [] then [x] else (x + (head xs) ) : casiGauss(tail xs)

gauss [] = 0
gauss ls = (length (casiGauss (crazySort ls) )) * (head (casiGauss (crazySort ls) ))
