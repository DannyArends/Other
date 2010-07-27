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

extern "C"
{
	#include <R.h>
	#undef ISNAN
	#define ISNAN(x) _isnan(x)
	#undef R_FINITE
	#define R_FINITE(x) _finite(x)
	
	void R_add_in_C(int *a,int *b,int *sum,bool *verbose){
		if(*verbose){
			Rprintf("Parameters to add up: a=%d b=%d\n",*a,*b);
		}
		
		(*sum) = (*a)+(*b);
		
		if(*verbose){
			Rprintf("Result stored in *sum: %d\n",*sum);
		}
		
	}
}