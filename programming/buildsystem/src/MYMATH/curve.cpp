/**
 * \file MYMATH/curve.cpp
 * \brief Code file, Implementation of concept: beziercurve
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "curve.h"


uint c[maxpoints];   // the binomial coefficients


/**
* C-routine to compute bezier curve coefficient, n! / (k!*(n-k)!)<br>
* bugs: none found<br>
* @param n uint<br>
*/
void ComputeCoeff (uint n){
  uint j,k;
  for (k=0;k<=n;k++){
    c[k] = 1;
    for (j = n;j>=k+1;j--)
      c[k] *=j;
    for (j = n-k;j>=2;j--)
      c[k] /= j;
  }
}

/**
* C-routine to compute one blending value of a point on the bezier curve<br>
* bugs: none found<br>
* @param n uint<br>
* @param k uint<br>
* @param t double<br>
*/
double BlendingValue (uint n, uint k, double t){ 
  // compute  c[k]*t^k * (1-t)^(n-k)
  if(k >= maxpoints) k = maxpoints-1;
  uint j;
  double bv;
  bv = c[k];
  for (j=1; j<=k;j++){
    bv *= t;
  }
  for (j = 1;j<=n-k;j++){
    bv *= (1-t);
  }
  return bv;
}

/**
* C-routine to compute one point on the Bezier curve - fixed value of t<br>
* bugs: none found<br>
* @param t double value that is used as a fixed value in calculation<br>
* @param n uint<br>
* @param p point& current point<br>
* @param ctrlPts pointvector of controlpoints for the beziercurve<br>
*/
void ComputePoint (double t, uint n, point & p, pointvector ctrlPts){ 
  uint k;
  if(n >= maxpoints) n = maxpoints-1;
  double b;
  p.x = 0.0;
  p.y = 0.0;
  for (k = 0; k<=n;k++){
    b = BlendingValue (n,k,t);
    p.x += ctrlPts.pt[k].x*b;
    p.y  += ctrlPts.pt[k].y*b;
  }
}

/**
* C-routine that calculates a beziercurve using a pointvector structure for controlpoints<br>
* Bezier itterations can be set, the output is a pointvector structure of beziercurve points<br>
* bugs: none found<br>
* @param controlPts pointvector of controlpoints for the beziercurve<br>
* @param numuinter uint with the number of itterations used to smooth the curve<br>
* @param curve pointvector& of curvepoints holding the generated beziercurve<br>
*/
void Bezier( pointvector controlPts, uint numuinter, pointvector& curve){
  if(numuinter >= maxpoints) numuinter = maxpoints-1;
  uint k;
  double t;
  ComputeCoeff (controlPts.num-1);
  curve.num = numuinter+1;
  for (k=0; k<=numuinter; k++){
    t = (double) k / (double) numuinter;
    ComputePoint (t, controlPts.num-1,curve.pt[k],controlPts);
  }
}
