/**
 * \file GUI/entities/normals.cpp
 * \brief Code file, Several routines to handle float[3] vectors
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "normals.h"

/**
* C-routine that calculates v1-v2 of two vectors<br>
* bugs: none found<br>
* @param v1 floatvector 1x3 holding the vector<br>
* @param v2 floatvector 1x3 holding the vector<br>
*/
float* vectordifference(float v1[3],float v2[3]){
  float* diff = new float[3];
  diff[0] = v1[0] - v2[0];
  diff[1] = v1[1] - v2[1];
  diff[2] = v1[2] - v2[2];
  return diff;
}

/**
* C-routine that sums 2 vectors<br>
* bugs: none found<br>
* @param v1 floatvector 1x3 holding the vector<br>
* @param v2 floatvector 1x3 holding the vector<br>
*/
float* vectorsum(float v1[3],float v2[3]){
  float* sum = new float[3];
  sum[0] = v1[0] + v2[0];
  sum[1] = v1[1] + v2[1];
  sum[2] = v1[2] + v2[2];
  return sum;
}

/**
* C-routine that multiplies a vector with a constant<br>
* bugs: none found<br>
* @param v floatvector 1x3 holding the vector<br>
* @param alpha float parameter holding the maginification factor<br>
*/
float* vectormultiply(float v[3],float alpha){
  float* factor = new float[3];
  factor[0] = v[0] * alpha;
  factor[1] = v[1] * alpha;
  factor[2] = v[2] * alpha;
  return factor;
}

/**
* C-routine that calculates the magintude of a vector<br>
* bugs: none found<br>
* @param v floatvector 1x3 holding the vector<br>
*/
float vectormagnitude(float v[3]){
  return(sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])));
}

/**
* C-routine that normalizes a vector<br>
* bugs: none found<br>
* @param v floatvector 1x3 holding the vector to normalize<br>
*/
void vectornormalize(float v[3]){
  // calculate the length of the vector
  float len;
  len = vectormagnitude(v);
  if (len == 0.0f) len = 1.0f;

  // reduce to unit size
  v[0] /= len;
  v[1] /= len;
  v[2] /= len;
}

/**
* C-routine that normalizes a vector<br>
* bugs: none found<br>
* @param v floatvector 1x3 holding the vector to normalize<br>
*/
float* vectornormalized(float v[3]){
  // calculate the length of the vector
  float* normal = new float[3];
  float len;
  len = vectormagnitude(v);
  if (len == 0.0f) len = 1.0f;

  normal[0] = v[0] / len;
  normal[1] = v[1] / len;
  normal[2] = v[2] / len;
  return normal;
}

/**
* C-routine that finds a normalized normal vector for a triangle<br>
* bugs: none found<br>
* @param v floatmatrix 3x3 holding the three points of the triangle<br>
*/
float* trianglefindnormal(float v[3][3]){
  float a[3];
  float b[3];
  float* normal = new float[3];

  a[0] = v[0][0] - v[1][0];
  a[1] = v[0][1] - v[1][1];
  a[2] = v[0][2] - v[1][2];

  b[0] = v[1][0] - v[2][0];
  b[1] = v[1][1] - v[2][1];
  b[2] = v[1][2] - v[2][2];

  // calculate the cross product and place the resulting vector
  normal[0] = (a[1] * b[2]) - (a[2] * b[1]);
  normal[1] = (a[2] * b[0]) - (a[0] * b[2]);
  normal[2] = (a[0] * b[1]) - (a[1] * b[0]);

  // normalize the normal
  vectornormalize(normal);
  return normal;
}
