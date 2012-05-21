# RSA encryption implementation
# Last modified Feb, 2012
# First written Feb, 2012
# (c) 2012 Danny Arends

#######  Helper function  #######

#Test to see if a number is prime
prime <- function(x){
  if(x <2) return(FALSE)
  if(x==2) return(TRUE)
  !any(x%%(2:round(sqrt(x)))==0)
}

#Calculate the x'th prime number (also suitable for vectors 1:4)
xthprime <- function(x, verbose = FALSE){
  s <- proc.time()
  cnt    <- 0
  pn     <- 0
  primes <- NULL
  for(n in sort(x)){
    sn = n
    n <- n-pn
    while(n != 0){
      cnt <- cnt+1
      if(prime(cnt)) n <- n-1
    }
    primes <- c(primes,cnt)
    pn <- sn
  }
  if(verbose) cat("Primes took:",(proc.time()-s)[3],"secs\n")
  primes
}

#Calculate the greatest common divisor of a and b
gcd <- function(a,b){
  while(a %% b != 0){
    tmp = a%%b
    a   = b;
    b   = tmp;
  }
  b
}

#Calculate 'large modulair powers'
mod.pow <- function(base, exponent, modulus){
  cnt <- 1
  for(e in 1:exponent){
    cnt <- (cnt * base) %% modulus
  }
  cnt
}
