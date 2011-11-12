#
# callD.R
# copyright (c) 2011 Danny Arends
# 
# callD use the C interface to call the example D 2.0 function
#

callD <- function(verbose = FALSE){
  if(!has(".has_d")){
    warning(.has_d_warning)
    #Alternative implementation of the D code
  }else{
    .C("R_test_function", PACKAGE="Ddll")
  }
}
