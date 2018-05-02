# Ejercicios Resueltos de primeros parciales

## Segundo cuatri 2017 - Ejercicio 2
### Inciso a

gamma > M : sigma ; gamma > N : [rt{sigma,tau}]
-----T-rose
gamma > rose(M, N) : rt(sigma, tau)

gamma |> M : rt(sigma1, sigma2) ;
gamma |> F : sigma1->tau1 ;
gamma |> G : sigma2->tau2
----T-map
gamma |> mapRT(F, G, M) : rt(tau1, tau2)

# ## Inciso b
V ::= ... | Rose(M, N)

Reglas de semantica para map (Rose no necesita porque dijimos que es valor)

###Inciso c
Reducir: 

mapRT(not, iZ, Rose(False, Rose(0,[]RTBool,Nat) :: []RTNat,Bool))

iz = \x : Nat. isZero(x)
not = \y : Bool. if y then False else True


---- E-map
mapRT(not, iZ, Rose(False, Rose(0,[]RTBool,Nat) :: []RTNat,Bool))

##Primer cuatri 2016 - Ejercicio 2

### Inciso a 
Reglas de tipado

gamma > M : sigma
---- T-matriz
gamma > Matriz(M) : MatrizInfinitasigma

gamma > N, O : Nat gamma > M : MatrizInfinitasigma 
---- T-melem
gamma > M[N][O] : sigma

gamma > N, O : Nat gamma > M : MatrizInfinitasigma gamma > P : sigma
---- T-massign
gamma > M[N][O] <- P : MatrizInfinitasigma

### Inciso b
Derivar (si se puede) el juicio de tipado para:

{f : Bool -> Bool} > (Matriz(f)[Succ(0)][0]<-(\x:Bool. True))[0][Succ(0)] : Bool->Bool
								---T-var---                                                  ---T-true---
								C > f:Bool->Bool                                             C U {x:Bool} > True:Bool
								---TMatriz---                       ---T-succ T-zero---      ---T-abs---
								C > Matriz(f):MatrizInf{Bool->Bool} C > Succ(0), 0 :Nat C > (\x:Bool. True):Bool-> Bool
--T-zero-- --T-Succ y T-Zero--  ---T-assign ----
C > 0:Nat 	C > Succ(0):Nat		C > (Matriz(f)[Succ(0)][0]<-(\x:Bool. True)):MatizInf{Bool->Bool}
---- T-melem (renombro el contexto a C)
{f : Bool -> Bool} > (Matriz(f)[Succ(0)][0]<-(\x:Bool. True))[0][Succ(0)] : Bool->Bool


### Inciso c

V ::= ... | Matriz(M) | M[N][O] <- P

N->N'
--- E-MNat1
M[O][N]->M[O][N']

N->N'
--- E-MNat2
M[N][V]->M[N'][V]

M->M'
---- E-Melem 
M[V1][V2] -> M'

-----E-baseMat
Matriz(M)[V1][V2] -> M (Notar que es byname, no reducimos antes de devolver M)

(Notar que faltan las reglas que reducen los indices)
(V1 y V2 podrian no ser natulares en forma normal)

(V1 = V3) and (V2 = v4)
-----E-assign1
(M[V1][V2] <- P)[V3][V4] -> P

not(V1 = V3) or not(V2 = v4)
-----E-assign2 (La que nos permite buscar recursivamente en la matriz)
(M[V1][V2] <- P)[V3][V4] -> M[V3][V4]

###inciso D


(\y:Bool.y)
----E-BaseMat
Matriz(\y:Bool.y)[0][Succ(0)]
--- E-assign2
(Matriz(\y:Bool.y)[Succ(0)][0]<-(\x:Bool.true))[0][Succ(0)]

## Primer cuatri 2015 - Ejercicio 1

### Inciso a 

Funcion entrelazar

	entrelazar::[a]->[a]->[a]
	entrelazar xs ys = concat(zipWith (\x y -> x:y:[]) xs ys)
	entrelazar' xs ys = concatMap (\p -> (fst p):(snd p): []) zip xs ys

Probado empiricamente que funciona con infinitas, pero ni idea porque.

### Inciso b

	duplicarApariciones::[a]->[a]
	duplicarApariciones as = entrelazar as as
	
### Inciso c
	
	factorial = dynprog f 1 
		where f = (\res -> (head res) * (length res))
		--length res capaz necesita un +1
	
### Inciso d
