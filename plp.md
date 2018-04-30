#Resueltos

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

### Inciso b
V ::= ... | Rose(M, N)

Reglas de semantica para map (Rose no necesita porque dijimos que es valor)

###Inciso c
Reducir: 

mapRT(not, iZ, Rose(False, Rose(0,[]RTBool,Nat) :: []RTNat,Bool))

iz = \x : Nat. isZero(x)
not = \y : Bool. if y then False else True


---- E-map
mapRT(not, iZ, Rose(False, Rose(0,[]RTBool,Nat) :: []RTNat,Bool))
