#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

enum modelmethod   { FORWARD = 'F', BACKWARD = 'B' };
enum scanmethod    { FAST = 'F', COMPLETE = 'C' };
enum markertypes   { CLASSICMARKER = 1, SNPMARKER = 2, EPIMARKER = 3 };
enum cofactortypes { ENVIROMENT = 1, MARKERUNDECIDED = 2, MARKERDECIDED = 3, QTL = 4 };
enum sextypes      { NOSEX = 0, XXXY = 1, ZZZW = 2 };
enum operatortype  { AND = '+', CROSS = '*', BLEFT = '(', BRIGHT = ')' };

typedef struct{
  markertypes type;
  char* alleles;
  int chromosome;
  double cmposition;
} markertype;

typedef struct{
  const char* name;
  int numchromosomes;
  int numalleles;
  int sex;
  sextypes sextype;
} speciestype;

typedef struct{
  int nummarkers;
  int numoperators;
  markertype* markers;
  operatortype* operators;
} generationf;

typedef struct{
  int id;
  int           numgenerations;
  int*          generation;
  generationf*  formula;
  markertype*   markertypedef;  
  int           numcofactors;
  char*         cofactors;
} populationtype;

typedef struct{
  int id;
  char* name;
  markertype* genotype;
  int numtraits;
  double* traits;
} individualtype;

#endif
