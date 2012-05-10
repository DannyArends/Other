/**
 * \file GUI/entities/force.h
 * \brief Header file, for GUI/entities/force.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef FORCE_H_
  #define FORCE_H_
  #include "ENTITIES.h"

  int powerint(int a,int exp);
  float powerfloat(float a,int exp);
  float difference(const float x,const float y);
  
  /** 
      * \brief Representing the abstract concept of force (Newton).
      */     
class force:public moveable<object>, public node<entity>{
public:
  force();
	~force(void);
  void setforce(float x,float y,float z);
	void setlife(int life);
  void setsleep(int life);
  bool age(int life);
	void setrandomness(int factor);
  void render(void);
private:
  void effect(void);
	int maxlife,curlife,sleep;
  bool persist;  
	int randomness;
};

#endif
