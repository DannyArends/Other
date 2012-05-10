# RSA encryption implementation
# Last modified Feb, 2012
# First written Feb, 2012
# (c) 2012 Danny Arends

#Function to decrypt
decrypter <- function(x,cypher){ mod.pow(x, cypher[[4]], cypher[[2]]) }
encrypter <- function(x,cypher){ mod.pow(x, cypher[[3]], cypher[[2]]) }

#Create a look up table 
create.lookup <- function(elements, cypher, fun=decrypter, verbose = TRUE){
  s <- proc.time()
  lutable <- NULL
  for(x in elements){
    index <- fun(x,cypher)
    if(index < length(ALPHABET)){
      lutable <- rbind(lutable,c(x, ALPHABET[index]))
    }
  }
  if(verbose) cat("Lookup table:",(proc.time()-s)[3],"secs\n")
  lutable
}

#Translate a message using a lookup table
lookup <- function(msg, lutable, collapse=TRUE, verbose = TRUE){
  s <- proc.time()
  translated <- NULL
  for(i in msg){
    translated <- c(translated,lutable[which(lutable[,1] == i),2])
  }
  if(verbose) cat("Lookup:",(proc.time()-s)[3],"secs\n")
  if(collapse) translated <- paste(translated, collapse="")
  translated
}
