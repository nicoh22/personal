ejuno<-function(n){
cuenta<-c()
x<-1:639
t<-n
while( n > 0){
	z<-c()
	count<-0
	while( length(z) < 639){
		z <- c(z,sample(x, 5, replace=FALSE))
		z<-unique(z)
		count <- count+1
	}
	cuenta<-c(cuenta, count)
	n<-n-1
}
sum(cuenta)/t
}
