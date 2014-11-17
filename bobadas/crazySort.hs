crazySort [] = []
crazySort (x : xs) = x : (crazySort (reverse xs) )
