/**
 * \file GUI/widgets/square.h
 * \brief Header file, for GUI/widgets/square.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef SQUARE_H_
  #define SQUARE_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Two dimensional colored square.
      */      
  class square: public widget{
  public:
    square(void);
    void render(void);
  private:
    void init();
};

#endif
