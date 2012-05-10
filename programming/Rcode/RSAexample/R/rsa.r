# RSA encryption implementation
# Last modified Feb, 2012
# First written Feb, 2012
# (c) 2012 Danny Arends

source("functions.r")

#######  RSA key generation  #######

#Calculate the e value (public key part) of the RSA algorithm
getE <- function(N, pq){
  x <- round(N/2)
  coprime <- (pq[1]-1) * (pq[2]-1)
  while(x < N && gcd(x,coprime) != 1){
    x <- x + 1
    while(!prime(x)) x <- x + 1
  }
  x
}

#Calculate the d value (private key part) of the RSA algorithm
getD <- function(e,coprime){
  d <- 1
  while((e*d)%%coprime != 1){ d <- d+1 }
  d
}

#Generate an RSA cypher key
generateCypher <- function(strength = 10, n2, verbose = TRUE){
  if(missing(n2)){ #Generate 2 random primes
    pq <- xthprime(sample(5:(10*strength))[1:2])
  }else{ #Get the 2 primes
    pq <- xthprime(c(strength,n2))  
  }
  if(verbose) cat("Primes done:\t", pq[1], pq[2],"\n")
  N  <- pq[1] * pq[2]
  coprime <- (pq[1]-1) * (pq[2]-1)
  e  <- getE(N,pq)
  if(verbose) cat("Public key:\t",paste(N,"-",e,sep=""),"\n")
  d <- getD(e,coprime)
  if(verbose) cat("Private key:\t",paste(N,"-",d,sep=""),"\n")
  res <- list(pq,N,e,d)
  class(res) <- c(class(res),"cypher")
  res
}

#Output the cypher in a nice way
print.cypher <- function(x){
  cat("Public Key:\t",x[[2]],"-",x[[3]],"\n",sep="")
  cat("Private Key:\t",x[[2]],"-",x[[4]],"\n",sep="")
  cat("----\n",sep="")
  cat("Prime seeds:\t",paste(x[[1]],collapse=" "),"\n",sep="")
  cat("----\n",sep="")
}
