/**
 * \file GUI/entities/particle.h
 * \brief Header file, for GUI/entities/particle.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef PARTICLE_H_
  #define PARTICLE_H_
  #include "ENTITIES.h"
  
  /** 
  * \brief Three dimensional particle<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class particle:public entity{
  public:
  	particle(void);
  	~particle(void);
    void randomcolor(void);
  	void render(void);
  };

#endif
