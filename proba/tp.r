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
	cuenta<-c()
	x<-1:639
	t<-n
	while( t > 0){
		
	}
	
}
