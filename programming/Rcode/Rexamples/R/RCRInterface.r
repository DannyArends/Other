#####################################################################
#
# Add_in_C.R
#
# copyright (c) 2009, Danny Arends
# last modified March, 2008
# first written Unknown
#
# Contains: AddinC
#
######################################################################



AddinC <- function(a,b,verbose=T){
	result <- .C("R_add_in_C",as.integer(a),as.integer(b),as.integer(0),as.logical(verbose))
	result[[3]]
}
