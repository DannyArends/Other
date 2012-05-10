/**
 * \file GUI/entities/entity.cpp
 * \brief Code file, Implementation of class: \ref entity
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "ENTITIES.h"

entity::entity(void){
  this->r           =0.0f;
  this->g           =0.0f;
  this->b           =0.0f;   
  this->alpha       =1.0f; 
  this->size        =0.1f;
  this->maxlife     = 0;
  this->curlife     = 0;
}

entity::~entity(void){

}

void entity::setlife(int life){
  this->maxlife=life;
}

int entity::getlife(void){
  return this->maxlife;
}

int entity::getage(void){
  return this->curlife;
}

float entity::getsize(){
  return this->size;
}

void entity::reset(void){
  this->curlife=0;
  this->setimpulse(0.0f,0.0f,0.0f);
}

bool entity::age(int life){
  this->curlife += life;
  if(this->curlife >= this->maxlife){
    return false;
  }else{
    float mod;
    mod = 2*this->size;
    this->movelocation((this->getimpulse()[0]/(mod)),(this->getimpulse()[1]/(mod)),(this->getimpulse()[2]/(mod)));
    return true;
  }
}

void entity::setsize(float size){
  this->size=size;
}

void entity::setcolor(float r, float g, float b,float alpha){
  if(r>0) this->r=r;
  if(g>0) this->g=g;
  if(b>0) this->b=b;
  this->alpha=alpha;
}

void entity::setcolor(float r, float g, float b){
  if(r>0) this->r=r;
  if(g>0) this->g=g;
  if(b>0) this->b=b;
}
