/**
 * \file GUI/camera.cpp
 * \brief Code file, Implementation of class: \ref camera
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "camera.h"

camera::camera() : object3d::object3d(){
  this->rotation[0]=0;
  this->rotation[1]=90;
  this->rotation[2]=0;
  this->followmode=false;
}

void camera::follow(entity* target){
  this->target=target;
  this->followmode=true;
}

void camera::update(uint life){
  if(this->followmode){
    float loc[3];
    loc[0] = this->target->getx();
    loc[1] = this->target->gety();
    loc[2] = this->target->getz();
    float cameramod = distancetotarget*cos((this->rotation[0]*PI)/180);
    loc[0] += cameramod*(cos((this->rotation[1]*10*PI)/180));
    loc[1] += sin((this->rotation[1]*10*PI)/180);
    loc[2] += cameramod*(sin((this->rotation[1]*10*PI)/180));
    this->setlocation(loc[0],loc[1],loc[2]);
  }
}

void camera::setrotation(float x,float y,float z){
  this->rotation[0]+=x;
  this->rotation[1]+=y;
  this->rotation[2]+=z;
}

float camera::getrotation(uint index){
  return this->rotation[index];
}

camera::~camera() {

}
