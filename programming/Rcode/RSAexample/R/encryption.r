# RSA encryption implementation
# Last modified Feb, 2012
# First written Feb, 2012
# (c) 2012 Danny Arends

source("rsa.r")

#!!! Define the alphabet of the allowed letters !!!#
#ALPHABET <- c(letters,LETTERS," ",",",".",":","\"","'","#","\n",as.character(0:9))

#######  Encryption/Decryption routines  #######

#Encrypt an unencoded message in ALPHABET
encrypt <- function(msg, cypher, verbose = TRUE){
  s <- proc.time()
  enc <- NULL
  for(char in unlist(strsplit(msg,""))){
    charid <- which(ALPHABET==char)
    enc <- c(enc,mod.pow(charid, cypher[[3]], cypher[[2]]))
  }
  if(verbose) cat("Encryption took:",(proc.time()-s)[3],"secs\n")
  enc
}

#Decrypt an encoded message to ALPHABET
decrypt <- function(msg, cypher, verbose=TRUE){
  s <- proc.time()
  dec <- NULL
  for(code in msg){
    dec <- c(dec,ALPHABET[mod.pow(code, cypher[[4]],cypher[[2]])])
  }
  if(verbose) cat("Decryption took:",(proc.time()-s)[3],"secs\n")
  paste(dec,collapse="")
}
