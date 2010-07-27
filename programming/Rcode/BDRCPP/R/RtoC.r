#####################################################################
#
# RtoC.R
#
# copyright (c) 2009, Danny Arends
# last modified Nov, 2009
# first written 2008
#
# Contains: addinC, startC
#
######################################################################


addinC <- function(a,b){
	result <- .Call("R_add_in_C", a, b)
	result
}

startC <- function(arguments){
	result <- .Call("Smain", nrow(arguments),arguments)
	result
}
