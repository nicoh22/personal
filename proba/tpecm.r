estimMV<-function(n, theta){
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


