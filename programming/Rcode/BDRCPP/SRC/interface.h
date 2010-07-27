/**********************************************************************
 * 
 * R_interface.h
 *
 * copyright (c) 2009 Danny Arends
 * last modified Nov, 2009
 * first written Apr, 2009
 *
 * C functions for the Rexamples package
 * Contains: R_add_in_C
 *
 **********************************************************************/
#include "includes.h"
extern "C"
{
  SEXP R_add_in_C(SEXP Ra, SEXP Rb);
  SEXP Smain(int* argc,char* argv[]);
}
