/**
 * \file GUI/entities/normals.h
 * \brief Header file, for GUI/entities/normals.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef NORMALS_H_
  #define NORMALS_H_
  #include "ENTITIES.h"
  
  float*  vectordifference(float v1[3],float v2[3]);
  float*  vectorsum(float v1[3],float v2[3]);
  float*  vectormultiply(float v[3],float alpha);
  float   vectormagnitude(float v[3]);
  void    vectornormalize(float v[3]);
  float*  vectornormalized(float v[3]);
  float*  trianglefindnormal(float v[3][3]);

#endif
