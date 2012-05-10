/**
 * \file GUI/entities/force.cpp
 * \brief Code file, Implementation of class: \ref force
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "force.h"


/**
* \brief C-routine to compute the power of an int<br>
*
* bugs: none found<br>
* @param a a in a^exp<br>
* @param exp exp in a^exp<br>
*/
int powerint(int a,int exp){
  if(exp==0) return 1;
  int s=a;
	for(int x=0;x<exp;x++){
		s*=a;
	}
	return s;
}

/**
* \brief C-routine to compute the power of a float<br>
*
* bugs: none found<br>
* @param a a in a^exp<br>
* @param exp exp in a^exp<br>
*/
float powerfloat(float a,int exp){
  if(exp==0.0) return 1;
  if(exp < 1) return 1/powerint((int)a,exp);
	float s=a;
	for(int x=0;x<exp;x++){
		s*=a;
	}
	return s;
}


/**
* \brief C-routine to compute the difference between two floats<br>
*
* bugs: none found<br>
* @param x float number 1<br>
* @param y float number 1<br>
*/
float difference(const float x,const float y){
  if(x<=0 && y >= 0) return x-y;
  if(y<=0 && x >= 0) return y-x;
  if(x==y) return 0.0;
  if(x < y) return y-x;
  if(x > y) return x-y;
  return 0.0f;
}

/**
* C-routine to compute the normalized distance between 2 vectors in a very floaty way<br>
* bugs: none found<br>
* @param ax float number ax<br>
* @param ay float number ay<br>
* @param az float number az<br>
* @param bx float number bx<br>
* @param by float number by<br>
* @param bz float number bz<br>
*/
float distance(const float ax,const float ay,const float az,const float bx,const float by,const float bz){
  return (float)sqrt(powerfloat(difference(ax,bx),2)+powerfloat(difference(ay,by),2)+powerfloat(difference(az,bz),2));
}

/** 
* The force class<br>
* bugs: none found
*/
force::force(){
	this->maxlife = 0;
  this->curlife = 0;
  this->sleep = 0;  
  this->randomness = 0;
  this->persist=true;
}

/** 
* bugs: Needs to cleanup entities*
*/
force::~force(void){

}

/** 
* Sets the strength of the force in 3 directions<br>
* bugs: none found
* @param x float number for force in direction x<br>
* @param y float number for force in direction y<br>
* @param z float number for force in direction z<br>
*/
void force::setforce(float x,float y,float z){
  this->persist=false;
  this->setimpulse(x,y,z);
}

/** 
* Sets the lifetime a force should be allowed to act<br>
* bugs: none found
* @param life lifespan<br>
*/
void force::setlife(int life){
  this->maxlife=life+this->sleep;
}

/** 
* Sets the lifetime a force should sleep after acting<br>
* bugs: none found
* @param life lifespan<br>
*/
void force::setsleep(int life){
  this->sleep=life;
  this->maxlife+=life;
}

/** 
* Age the forces lifetime and act on all the entities<br>
* bugs: none found
* @param life lifespan to age<br>
*/
bool force::age(int life){
  //if(this->getparent()) setlocation(this->getparent()->getx(),this->getparent()->gety(),this->getparent()->getz());
  this->curlife += life;
  if(this->persist){
    this->effect();
  }else{
    if(!(this->curlife < this->sleep)){
      if((this->curlife <= this->maxlife)) this->effect();
      if(this->curlife == this->maxlife){
        if(this->persist) this->curlife=0;
      }
    }
  }
  return false;
}

/** 
* Add some randomness to the force<br>
* bugs: none found
* @param factor randomnessfactor from 0 (off) to 1000 (very random)<br>
*/
void force::setrandomness(int factor){
  this->randomness=factor;
}

/** 
* Calculation of effect of force on all entities attached<br>
* bugs: none found
*/
void force::effect(){
  float* effect;
  float* direction;
  float m;

  for(uint t=0;t<this->getchildren().size();t++){
    object3d* target = this->getchildren()[t];
    if(this->persist){
      direction=vectordifference(this->getparent()->getlocation(),target->getlocation());
      m = vectormagnitude(direction);
      vectornormalize(direction);
    }else{
      direction = this->getimpulse();
      m=1;
    }
    if(this->getparent()){
      effect=vectormultiply(direction,((entity*)this->getparent())->getsize()/240+1/sqrt(m));
    }else{
      effect=vectormultiply(direction,1/sqrt(m));
    }
    if(this->randomness != 0){
      float rfactor = (this->randomness/2);
      effect[0] += (float(rand()%this->randomness)-rfactor)/1000;
      effect[1] += (float(rand()%this->randomness)-rfactor)/1000;
      effect[2] += (float(rand()%this->randomness)-rfactor)/1000;
    }
    //printf("effect:%f %f %f \n ",effect[0],effect[1],effect[2]);
    ((entity*)target)->addimpulse(effect[0],effect[1],effect[2]);
    delete(effect);
    delete(direction);
  }
}

void force::render(void){

}
