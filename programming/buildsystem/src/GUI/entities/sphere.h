/**
 * \file GUI/entities/sphere.h
 * \brief Header file, for GUI/entities/sphere.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

 #ifndef SPHERE_H_
  #define SPHERE_H_
  
  #include "ENTITIES.h"
  
  /** 
      * \brief Three dimensional sphere, with optional surface
      */
  class sphere:public bufferable<entity>{
  public:
    sphere(void);
   ~sphere(void);
    void setradius(float radius);
    force* getgravity(void);
    void addterrain(terrain* t);
    void setprecision(uint p);
    bool buffer(void);
    void render(void);
  private:
    void printopengl(void);
    force* gravity;
    terrain* surface;
    GLuint displaylist;
    uint p;
    float twopi,pidtwo;
  };

#endif
