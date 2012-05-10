/**
 * \file GUI/entities/skeleton.h
 * \brief Header file, for GUI/entities/skeleton.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef SKELETON_H_
  #define SKELETON_H_
  #include "ENTITIES.h"
  
  /** 
      * \brief Skeleton structure usable for objects.
      */  
  class skeleton:public bufferable<entity>{
  public:
    skeleton(void);
    ~skeleton(void);
    bool buffer(void);
    void render(void);
  private:
    GLuint displaylist;
    void printopengl(void);
    bool buffered;
  };
#endif
