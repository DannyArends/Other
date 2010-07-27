/**********************************************************************
 * 
 * R_interface.cpp
 *
 * copyright (c) 2009 Danny Arends
 * last modified Apr, 2009
 * first written Apr, 2009
 *
 * C functions for the Rexamples package
 * Contains: R_add_in_C
 *
 **********************************************************************/
#include "interface.h"
extern "C"
{
  SEXP R_add_in_C(SEXP Ra, SEXP Rb){
    int a, b;
    SEXP Rval;
    Ra = coerceVector(Ra, INTSXP);
    Rb = coerceVector(Rb, INTSXP);
    
    a = INTEGER(Ra)[0];
    b = INTEGER(Rb)[0];
    
    PROTECT(Rval = allocVector(INTSXP, 1));
    INTEGER(Rval)[0] = a+b;
    UNPROTECT(1);
    return Rval;
  }

  SEXP Smain(int* argc,char* argv[]){
    int argcount = (int)*argc;
    printf("Number of arguments: %d",argcount);
    SEXP Rval;

    return Rval;
  }
}
