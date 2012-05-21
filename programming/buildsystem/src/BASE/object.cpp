/**
 * \file BASE/object.cpp
 * \brief Code file, Implementation of class: \ref object, \ref object2d, \ref object3d
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "object.h"

/*********************************************************************/

object3d::object3d(void) : object::object() {
  this->location[0] =0.0f;
  this->location[1] =0.0f;
  this->location[2] =0.0f;
}

object3d::~object3d(void){

}

void object3d::setlocation(float x, float y, float z){
  this->location[0]=x;
  this->location[1]=y;
  this->location[2]=z;
}

void object3d::movelocation(float x, float y, float z){
  this->location[0]+=x;
  this->location[1]+=y;
  this->location[2]+=z;
}

float object3d::getx(void){
  return this->location[0];
}

float object3d::gety(void){
  return this->location[1];
}

float object3d::getz(void){
  return this->location[2];
}

float* object3d::getlocation(void){
  return this->location;
}

/*********************************************************************/

object2d::object2d(void) : object::object(){
  this->location[0] =0;
  this->location[1] =0;
}

object2d::~object2d(void){

}

void object2d::setlocation(int x, int y){
  this->location[0]=x;
  this->location[1]=y;
}

void object2d::movelocation(int x, int y){
  this->location[0]+=x;
  this->location[1]+=y;
}

void object2d::save(void){
  //TODO SAVE
}

int object2d::getx(void){
  return this->location[0];
}

int object2d::gety(void){
  return this->location[1];
}

int* object2d::getlocation(void){
  return this->location;
}

void object2d::setsize(int x,int y){
  this->size[0]=x;
  this->size[1]=y;
}

int object2d::getsizex(void){
  return this->size[0];
}

void object2d::setsizex(int x){
  this->size[0] = x;
}

int object2d::getsizey(void){
  return this->size[1];
}

void object2d::setsizey(int y){
  this->size[1] = y;
}

