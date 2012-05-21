/**
 * \file GUI/entities/bone.h
 * \brief Header file, for GUI/entities/bone.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef BONE_H_
  #define BONE_H_
  #include "ENTITIES.h"
  
  /** 
  * \brief \brief Class representing a single bone, the substructure of a skeleton.
  */
  class bone:public bufferable<entity>{
  public:
    bone(void);
    ~bone(void);
    void setorientation(float x,float y,float z);
    void setlength(float l);
    float getlength(void);
    bool buffer(void);
    void render(void);
  private:
    GLuint displaylist;  
    void printopengl(void);
    bool buffered;
    float length;
    float orientation[3];
  };
#endif
