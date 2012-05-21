/**
 * \file GUI/entities/line.h
 * \brief Header file, for GUI/entities/line.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef LINE_H_
  #define LINE_H_
  #include "ENTITIES.h"

  /** 
      * \brief Three dimensional line
      */  
  class line:public entity{
    public:
    	line(void);
    	~line(void);
      void setendlocation(float x, float y, float z);
      void randomcolor(void);
    	void render(void);
    private:
      float endlocation[3];
  };

#endif
