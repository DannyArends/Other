/**
 * \file GUI/entities/turtle.h
 * \brief Header file, for GUI/entitiess/turtle.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef TURTLE_H_
  #define TURTLE_H_
  #include "ENTITIES.h"
  /** 
      * \brief Draws a three dimensional turtle graphic
      */
  class turtle:public entity{
    public:
    	turtle(void);
      ~turtle(void);
    	void decode(void);
      void randomcolor(void);
      void render(void);
    private:
      int itteration;
      uint max_length;
      string axiom;
      int hor_speed,vert_speed;
      int hori_rot,vert_rot;
      float storedloc[3];
      lsystem<char, string> system;
  };

#endif
