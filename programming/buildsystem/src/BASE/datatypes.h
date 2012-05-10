/**
 * \file BASE/datatypes.h
 * \brief Header file, for BASE/datatypes.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 

#ifndef DATATYPES_H_
  #define DATATYPES_H_

  #include "BASE.h"

  bvector newbvector(uint dim);
  dvector newdvector(uint dim);
  cvector newcvector(uint dim);
  ivector newivector(uint dim);

  void printdvector(dvector v, uint dim);
  void printcvector(cvector v, uint dim);
  void printivector(ivector v, uint dim);

  dmatrix newdmatrix(uint rows, uint cols);
  cmatrix newcmatrix(uint rows, uint cols);
  imatrix newimatrix(uint rows, uint cols);

  void printdmatrix(dmatrix m, uint rows, uint cols);
  void printcmatrix(cmatrix m, uint rows, uint cols);
  void printimatrix(imatrix m, uint rows, uint cols);

  void freematrix(void **m, uint rows);
  void freevector(void *v);

#endif
