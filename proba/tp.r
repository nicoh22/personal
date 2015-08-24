#Nicolas Carlos Hernandez
#LU 122/13

#Todas las funciones se llaman con un parametro que determina la cantidad 
#de veces que se realiza el experimento. A partir de esos valores se realiza
#un promedio para estimar la media.

eja<-function(n){ 
	cuenta<-0
	x<-1:639 #vector a samplear por los sobres
	t<-n
	while( t > 0){
		faltantes<-x
		count<-0 # cuenta la cantidad de sobres que necesito para llenar album 
		while( length(faltantes) != 0){
			z <- sample(x, 5, replace=FALSE) # compro un sobre
			faltantes<-faltantes[! faltantes %in% z] #saco las del sobre
			count <- count+1 
		}
		cuenta<-cuenta+count #acumulo resultados parciales
		t<-t-1
	}
	cuenta/n #calculo la media
}

ejb<-function(n){ #misma funcion pero con replace=TRUE
	cuenta<-0
	x<-1:639
	
	t<-n
	while( t > 0){
		faltantes<-x
		count<-0
		while( length(faltantes) != 0){
			z <- sample(x, 5, replace=TRUE)
			faltantes<-faltantes[! faltantes %in% z]
			count <- count+1
		}
		cuenta<-cuenta + count
		t<-t-1
	}
	cuenta/n
}

ejc<-function(n){
	cuenta<-0
	x<-1:639
	t<-n
	vpeso<- rep.int(c(1/2000,(1-10/2000)/639),c(10,629)) #vector de pesos
	while( t > 0){
		faltantes<-x
		count<-0
		while( length(faltantes) != 0){
			z <- sample(x, 5, replace=TRUE, prob=vpeso) 
			faltantes<-faltantes[! faltantes %in% z]
			count <- count+1
		}
		cuenta<-cuenta+count
		t<-t-1
	}
	cuenta/n
}


ejd<-function(n){
	prim<-0 #dividido por n sera la media del que termino primero
	seg<-0	#idem con el que termino segundo
	x<-1:639
	t<-n
	while( t > 0){ #ciclo cantidad especificada de veces
		cuentag<-0
		cuentap<-0
		pedro<-x #Las que le faltan para completar album a Pedro
		gaston<-x #idem con Gaston
		while(length(pedro) != 0 && length(gaston) !=0 ){ #hasta que alguno llene album
			sobreg<-sample(x, 5, replace=FALSE)
			sobrep<-sample(x, 5, replace=FALSE)
			repp<-sobrep[! sobrep %in% pedro] #me quedo con los repetidos de Pedro
			repg<-sobrep[! sobreg %in% gaston] #y de Gaston
			pedro<-pedro[! pedro %in% sobrep]
			gaston<-gaston[! gaston %in% sobreg]
			pedro<-pedro[! pedro %in% repg]#Gaston le da sus repes a Pedro
			gaston<-gaston[! gaston %in% repp]# y viceversa
			cuentag<-cuentag+1
			cuentap<-cuentap+1#cuento los sobres que compre			
		}
		if(length(pedro) == 0){#pedro termino primero
			prim<-prim+cuentap 
			while(length(gaston)!=0){ #sigue Gaston por su cuenta
				sobreg<-sample(x, 5, replace=FALSE)
				gaston<-gaston[! gaston %in% sobreg]
				cuentag<-cuentag+1
			}
			seg<-seg+cuentag
		}else{#gaston termino primero
			prim<-prim+cuentag
			while(length(pedro)!=0){ #sigue Pedro por su cuenta
				sobrep<-sample(x, 5, replace=FALSE)
				pedro<-pedro[! pedro %in% sobrep]
				cuentap<-cuentap+1
			}
			seg<-seg+cuentap
		}
		t<-t-1
	}
	c(prim/n, seg/n) #devuelve la media del que termino primero y del segundo
}

# Media estimada luego de 1000 experimentos:
# ejercicio a: 894.188
# ejercicio b: 888.398
# ejercicio c: 1236.181
# ejercicio d: 
#		el primero: 551.055
#		el segundo: 897.626

#Vemos que el caso del ejercicio "c" (donde hay "figuritas dificiles") es el
#que necesita mayor cantidad de sobres, mientras que el ejercicio "d" provee
#una ventaja muy significativa al que completa el album primero y al segundo 
#lo deja con una media similar al caso "a" y "b"

