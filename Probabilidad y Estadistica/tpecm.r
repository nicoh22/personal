estimMV<-function(n, theta){
  set.seed(124)
  Nrep<-1000
	i<-1
	estimadores<-rep(NA, Nrep)
	while(i <= Nrep){
		muestra<-runif(n, max = theta)
		estimadores[i]<-max(muestra)
		i<-i+1
	}
	estimadores<-estimadores - theta
	estimadores<-estimadores^2
	suma<-sum(estimadores)
	ecm<-suma/Nrep
	ecm
}

estimMO<-function(n, theta){
  set.seed(124)
  Nrep<-1000
	i<-1
	estimadores<-rep(NA, Nrep)
	while(i <= Nrep){
		muestra<-runif(n, max = theta)
		estimadores[i]<-2 * mean(muestra)
		i<-i+1
	}
	estimadores<-estimadores - theta
	estimadores<-estimadores^2
	suma<-sum(estimadores)
	ecm<-suma/Nrep
	ecm
}


icExacto<-function(alpha, theta, n){
  set.seed(124)
  Nrep<-1000
	i<-1
	longitudes<-rep(NA, Nrep)
	while(i <= Nrep){
		muestra<-runif(n, max = theta)
		maximo<-max(muestra)
		a<-maximo/((1 - alpha/2)^(1/n))
		b<-maximo/((alpha/2)^(1/n))
		longitudes[i]<-b-a
		i<-i+1
	}
	longEstim<-mean(longitudes)
	longEstim
}

icAsin<-function(alpha, theta, n){
  set.seed(124)
  Nrep<-1000
	i<-1
	longitudes<-rep(NA, Nrep)
	while(i <= Nrep){
		muestra<-runif(n, max = theta)
		promedio<-mean(muestra)
		cuantil<-qnorm(1-alpha/2)
		a<-2*promedio - 2*cuantil*promedio/sqrt(3*n)
		b<-2*promedio + 2*cuantil*promedio/sqrt(3*n)
		longitudes[i]<-b-a
		i<-i+1
	}
	longEstim<-mean(longitudes)
	longEstim
}

  set.seed(124)
  estimMO(5, 1)
  estimMO(5, 10)
  estimMO(5, 40)
  estimMO(30, 1)
  estimMO(30, 10)
  estimMO(30, 40)
  estimMO(60, 1)
  estimMO(60, 10)
  estimMO(60, 40)
  
  estimMV(5, 1)
  estimMV(5, 10)
  estimMV(5, 40)
  estimMV(30, 1)
  estimMV(30, 10)
  estimMV(30, 40)
  estimMV(60, 1)
  estimMV(60, 10)
  estimMV(60, 40)  
  
  icExacto(0.1, 1, 5)
  icExacto(0.1, 1, 30)
  icExacto(0.1, 1, 60)
  icAsin(0.1, 1, 5)
  icAsin(0.1, 1, 30)
  icAsin(0.1, 1, 60)
