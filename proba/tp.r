eja<-function(n){
	cuenta<-c()
	x<-1:639
	t<-n
	while( t > 0){
		z<-c()
		count<-0
		while( length(z) < 639){
			z <- c(z,sample(x, 5, replace=FALSE))
			z<-unique(z)
			count <- count+1
		}
		cuenta<-c(cuenta, count)
		t<-t-1
	}
	sum(cuenta)/n
}

ejb<-function(n){
	cuenta<-c()
	x<-1:639
	t<-n
	while( t > 0){
		z<-c()
		count<-0
		while( length(z) < 639){
			z <- c(z,sample(x, 5, replace=TRUE))
			z<-unique(z)
			count <- count+1
		}
		cuenta<-c(cuenta, count)
		t<-t-1
	}
	sum(cuenta)/n
}

ejc<-function(n){
	cuenta<-0
	x<-1:639
	t<-n
	vpeso<- rep.int(c(1/2000,(1-10/2000)/639),c(10,629))
	while( t > 0){
		z<-c()
		count<-0
		while( length(z) < 639){
			z <- c(z,sample(x, 5, replace=TRUE, prob=vpeso))
			z<-unique(z)
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
		pedro<-x
		gaston<-x
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
