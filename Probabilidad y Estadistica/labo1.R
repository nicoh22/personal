#bienvenidos!
#R ignora todo lo que aparece despues del signo #. permite asi comentar el codigo.

x<-c(1,2,3) # c de concatenar los valores entre parentesis
x+3 # suma el tres en cada coordenada
x*3 #multiplica por tres cada coordenada-
length(x) #da el tamaño del vector 
sum(x) #calcula la suma de los elementos del vector
mean(x) #calcula el promedio de los valores.

nombres <- c("José", "Pedro", "Agustín")
nombres


#vectores utilies
x1<-1:5
x2<-seq(1,10,by=0.1) #por paso
x3<-seq(1,10,length=100) #indicamos cuantos puntos 
x4<-rep(1,5)


x3[1]#Los arreglos se indexan desde el 1.
x3[3] #elige la tercer coordenada de x4
x3[c(1,5)] #elige las coordenadas 1 y 5


#operaciones con otro vector
y<-c(5,6,7)

x+y #suma vectores


#matrices
m<-matrix(c(1,2,3,4,5,6),2,3) #forma una matriz de 2x3 con el vector c(1,2,3,4,5,6), llenando  por columnas
t(m) #traspone la matrix m

m2<-matrix(c(2,0,0,3),2,2)
m2inv<-solve(m2) #solve calcula la inversa de una matriz 
m2inv%*%m2   #  %*% calculo productos matriciales. 


#tambien se pueden formar matrices juntando filas o columnas. 
cbind # pega columnas 

rbind #pega filas (rows)

#funciones 
sumamos<-function(a,b)
{
  a+b
}
sumamos(2,5)

#Comando for
#Quiero calcular 5 factorial
factorial<-1
for(i in 2:5)
{
  factorial<-i*factorial
}
factorial

factoriales<-function(n)
{
  factorial<-1
  for(i in 1:n)
  {
    factorial<-i*factorial
  }
  factorial
}
factoriales(5)
factoriales(1)
factorial(0)


#Comando if

favorables<-0
tiro<-sample(1:6,1,T)
if(tiro==5 )
{
  favorables<-1
}

favorables

#####################
#La ruina del jugador
#####################

#runif(k,a,b)  genera k numeros al azar en el intervalo (a,b)
u<-runif(1,0,1) #genera un numero random en (0,1)
u<0.5 #operacion logica, pregunta si es verdadera
#el TRUE pasa a 1 y el FALSE a 0, despues opero como numeros
paso<-1*(u<0.5)-1*(u>0.5)


Nrep<-1000
#rep(mongo,n) fabirca un vector con mongo n veces
final<-rep(NA, Nrep)
K<-5
for ( j in 1:Nrep)
{
x<-1
while (0<x && x<K) 
{
  
  u<-runif(1,0,1)
  paso<-1*(u<0.5)-1*(u>0.5)
   x<-x+paso
  } 
final[j]<-x
}


pg1<-mean(final==5)  #Estimo la probabilidad de ganar empezando con 1 ficha
pg2<-mean(final==5)  #Estimo la probabilidad de ganar empezando con 2 ficha
pg3<-mean(final==5)  #Estimo la probabilidad de ganar empezando con 3 ficha
pg4<-mean(final==5)  #Estimo la probabilidad de ganar empezando con 4 ficha


pg<-c(pg1,pg2,pg3,pg4)
ini<-seq(1:4)
plot(ini,pg)

xx<-seq(1:5)
yy<-3*xx


plot(xx,yy)

#Otro modo de sortear el paso
#funcion sample

####  COMANDO SAMPLE.
# ¿Qué hace?
sample(1:5, size=10, replace=T)

#sample(x, size , replace=T)

#genera un vector de tamaño size que tiene en cada cordenada un elemento
# de x el cual fue escogido al azar con reposición

# otro ejemplo
sample(c("José", "Agustín", "Pedro"), size=2, replace=T)

# Esto fue el muestreo con reposición. Para  esto va  la T.

sample(1:5, size=3, replace=F)


# Esto es muestro sin reposicion!
sample(1:5, size=5, replace=F)


#para sortear el paso con igual probabilidad
sample(c(1,-1),size=2,replace=T,prob=c(.5,.5))




#Otro modo de hacer estimar la probabilidad de la ruina del jugador
#variando las probabilidades de éxito (pensamos en la ruleta el apostador apuesta a negro)
p<-18/38 #probabilidad de éxito en cada jugada.
K<-100  #Dinero total
dineroini<-10 #dinero inicial del jugador
dinerotot<-K
Nrep<-10000
gana<-rep(0,Nrep)
for(i in 1:Nrep)
{
  dinerojug<-dineroini
  
  while(dinerojug>0&&dinerojug<dinerotot)
  {
    dinerojug=dinerojug+sample(c(1,-1),1,prob=c(p,1-p))
  }
  gana[i]=dinerojug
}

mean(gana==K)

#Otro posible problema: Estimar la cantidad de jugadas hasta que termina el juego


p<-18/38 #probabilidad de éxito en cada jugada.
K<-25  #Dinero total en juego
dineroini<-10 #dinero inicial del jugador
dinerotot<-K
Nrep<-10000
gana<-rep(NA,Nrep) #dinero que gana el jugador en cada replicación (0 o K)
juegos<-rep(NA,Nrep) #cuenta la cantidad de juegos hasta que termina en cada replicación
for(i in 1:Nrep)
{
  dinerojug<-dineroini
  jue<-0
  while(dinerojug>0&&dinerojug<dinerotot)
  {
    jue<-jue+1
    dinerojug=dinerojug+sample(c(1,-1),1,prob=c(p,1-p))
  }
  gana[i]=dinerojug
  juegos[i]<-jue
}

mean(gana==K)
mean(juegos)
#Calcular la cantidad promedio de juegos cuando gana y la cantidad promedio de juegos cuando pierde
totjuealganar<-0
totjuealperder<-0
for(i in 1:Nrep)
{
  if(gana[i]==K)
  {
    totjuealganar=totjuealganar+juegos[i]
  }
  else
  {
    totjuealperder=totjuealperder+juegos[i]
  }
}

promperdiendo<-totjuealperder/sum(gana==0)
promganando<-totjuealganar/sum(gana==K)

(totjuealperder+totjuealganar)/Nrep

###########################################################
# Acá empieza la clase vieja
###########################################################







#Ejercicio 1
#dado
#simulación del lanzamiento de un dado, fracuencia relativa de un número
#Correrlo 2 veces y ver si da lo mismo
favorables <-0
totales <- 10000
for (i in 1: totales)
{
  tiro<- sample(1:6,1,T)
  if(tiro==5)
    favorables <- favorables + 1
}
frecuencia <- favorables/totales
frecuencia


#pongo una semilla
set.seed(123)

favorables <-0
totales <- 10000
for (i in 1: totales)
{
  tiro<- sample(1:6,1,T)
  if(tiro==5)
    favorables <- favorables + 1
}
frecuencia <- favorables/totales
frecuencia



# cumpleaños: 
# Estimamos la probabilidad de que en un partido de futbol (22 jugadores)
# haya dos que cumplen el mismo dia
n<-22
favorables<-rep(1,1000)
for(j in 1:1000)
{
  coin<-rep(0,n)
  tiro<- sample(1:365,n,T)
  tiroor<-sort(tiro) #ordeno las fechas de cumple
  for(i in 2:n)
  {
    if(tiroor[i-1]==tiroor[i])
      coin[i]<-1
  }
  if(sum(coin)==0)
  {favorables[j]<-0}
}
sum(favorables)/1000

#la probabilidad es cercana a 1/2
############################
#Ejercicio 1
############################

set.seed(111) #fijo una semilla (para que las cuestiones aleatorias den igual en diferentes corridas)
runif(2,0,1)

favorables <-0
totales <- 1000
for (i in 1: totales)
{
  moneda <- sample(c(0,1),1,T)
  favorables <- favorables + moneda
}
frecuencia <- favorables/totales
frecuencia

#Copio todo y cambio totales (pruebo varias veces con totales fijo sin semilla) 
favorables <-0
totales <- 1000
for (i in 1: totales)
{
  moneda <- sample(c(0,1),1,T)
  favorables <- favorables + moneda
}
frecuencia <- favorables/totales
frecuencia

##################################
#Ejercicio 2
##################################

#Item a)

set.seed(111)
n<-2 #dados
m<-24 # tiradas
favorables<-0
totales<-1000 # repeticiones
for (j in 1:totales)
{
  gane<-0
  for (i in 1:m)
  {
    dados<-sample(1:6,n,T)
    if(sum(dados==rep(6,n))==2) gane<-1
  }
  if (gane==1) favorables<-favorables+1
}
probabilidad<-favorables/totales
probabilidad


#item c)

set.seed(111)
n<-3 #dados
m<-8 # tiradas
favorables<-0
totales<-1000 # repeticiones
for (j in 1:totales)
{
  gane<-0
  for (i in 1:m)
  {
    dados<-sample(1:6,n,T)
    if(sum(dados==rep(6,n))>=2) gane<-1
  }
  if (gane==1) favorables<-favorables+1
}
probabilidad<-favorables/totales
probabilidad


#item d)

1-pbinom(0,24,1/36)

1-pbinom(0,8,16/(6^3))


###########################
#Ejercicio 3 (11 de la uno)
###########################
#items a) , b) y d)
set.seed(111)
n<-2 #dados
s7<-0       #cantidad de veces que suman 7
si<-0       #suma impar
s7omas<-0   #suman 7 o mas
ai<-0       #alguno impar
totales<-1000 # repeticiones
for (j in 1:totales)
{
  dados<-sample(1:6,n,T)
  if(sum(dados)==7) s7<-s7+1
  if(sum(dados)/2-floor(sum(dados)/2)>0)si<-si+1
  if(sum(dados)>6)s7omas<-s7omas+1
  if((dados[1]/2-floor(dados[1]/2)>0)||(dados[2]/2-floor(dados[2]/2)>0))ai<-ai+1
}
s7/si
s7/s7omas
s7/ai


#item c
set.seed(111)
n<-2 #dados
s7yp2<-0  #suma y y segundo par
p2<-0     #el segundo es par
favorables<-0
totales<-1000 # repeticiones
for (j in 1:totales)
{
  dados<-sample(1:6,n,T)
  if((sum(dados)==7)&&(dados[2]/2-floor(dados[2]/2)==0)) s7yp2<-s7yp2+1
  if(dados[2]/2-floor(dados[2]/2)==0)p2<-p2+1
}
s7yp2/p2



#item e (si no nos avivamos que tiene que dar 0 podemos estimarlo igual)

set.seed(111)
n<-2 #dados
d1id2<-0     #dado 1 igual a dado 2
d1id2ys7<-0  #dado 1 igual a dado 2 y suman 7

totales<-1000 # repeticiones
for (j in 1:totales)
{
  dados<-sample(1:6,n,T)
  if(dados[1]==dados[2])d1id2<-d1id2+1
  if((dados[1]==dados[2])&&(dados[1]+dados[2]==7))d1id2ys7<-d1id2ys7+1
}

d1id2ys7/d1id2


####################################
#Ejercicio 4 (17 de la practica uno)
###################################
#item a)

#0 representara a la bola blanca y 1 a la bola roja
las2rojas<-0     #las 2 bolitas rojas
m3ylas2rojas<-0  #dado multiplo de 3 y las dos rojas
totales<-1000
for (j in 1:totales)
{
  A<-c(rep(0,3),rep(1,5))
  B<-c(rep(0,2),rep(1,1))
  dado<-sample(1:6,1,T)
  if((dado==3)||(dado==6))
  {
    b1<-sample(A,1,T)
    B<-c(B,b1)
    b2<-sample(B,1,T)
  }
  else
  {
    b1<-sample(B,1,T)
    A<-c(A,b1)
    b2<-sample(A,1,T)
  }
  if((b1==1)&&(b2==1))las2rojas<-las2rojas+1
  if(((dado==3)||(dado==6))&&(b1+b2==2)) m3ylas2rojas<-m3ylas2rojas+1
}
las2rojas/totales       #para item a)
m3ylas2rojas/las2rojas   #para item b)

