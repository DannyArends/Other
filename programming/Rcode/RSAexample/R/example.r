# RSA encryption implementation
# Last modified Feb, 2012
# First written Feb, 2012
# (c) 2012 Danny Arends

setwd("C:/github/RSA/R/")
#!!! Define the alphabet of the allowed letters !!!#
ALPHABET <- c(letters,LETTERS," ",",",".",":","\"","'","#","\n",as.character(0:9))

source("encryption.r")

# Example 1
# Generate a random cypher-key from first 100 (10*10) primes
cypher <- generateCypher(10)
cypher

msg.ori <- "Hellow World"
msg.enc <- encrypt(msg.ori, cypher)
msg.dec <- decrypt(msg.enc, cypher)
msg.dec

# Example 2
# Generate a non random cypher-key using the 5th and 9th prime
cypher <- generateCypher(5,9) 
cypher

msg.ori <- rep(sample(ALPHABET),100) #Bigger msg to test time

msg.enc <- encrypt(msg.ori, cypher)
msg.dec <- decrypt(msg.enc, cypher)
msg.dec

# Example 3 - Optimizing using a look-up table
source("optimize.r")

# Optimized decoding of the bigger msg
dec_lu_table <- create.lookup(unique(msg.enc), cypher, decrypter)
msg.dec <- lookup(msg.enc, dec_lu_table)

# Optimized encoding
enc_lu_table <- create.lookup(1:length(ALPHABET), cypher, encrypter)
enc_lu_table <- enc_lu_table[,c(2,1)] #Switch columns for encoding 
msg.enc <- lookup(unlist(strsplit(msg.ori,"")), enc_lu_table, FALSE)
