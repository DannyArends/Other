/**
 * \file MYMATH/curve.h
 * \brief Header file, for MYMATH/curve.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

 #ifndef CURVE_H_
  #define CURVE_H_
  #include "MYMATH.h"

  const uint maxpoints = 100;

  /**
  * \brief Structure holding a 2D point in float
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  struct point{
    double x,y;
  };

  /**
  * \brief Class holding \ref point objects
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  struct pointvector{
    uint    num;
    point*  pt;
  };
  

  //helper routines - compute the coefficient
  void ComputeCoeff (uint n);
  // compute the blending value
  double BlendingValue (uint n, uint k, double t);
  // compute one pouint on the Bezier curve
  void ComputePoint (double t, uint n, point& p, pointvector ctrlPts);
  // compute the array of Bezier pouints
  void Bezier(pointvector controlPts, uint numuinter, pointvector & curve);

#endif
