/**
 * \file BASE/object.h
 * \brief Header file, for BASE/object.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef OBJECT_H_
  #define OBJECT_H_
  
  #include "BASE.h"

  /** 
      * \brief The superclass of all three dimensional objects
      */
  class object3d: public object{
    public:
      object3d();
      ~object3d();
      void          setlocation(float x, float y, float z);
      void          movelocation(float x, float y, float z);
      float         getx(void);
      float         gety(void);
      float         getz(void);
      float*        getlocation(void);
    private:
      float         location[3];
  };
  
  /** 
      * \brief The superclass of all two dimensional objects
      */  
  class object2d: public object{
    public:
      object2d();
      ~object2d();
      void          setlocation(int x, int y);
      void          setsize(int x,int y);
      void          movelocation(int x, int y);
      int           getx(void);
      int           gety(void);
      int           getsizex(void);
      int           getsizey(void);
      void          setsizex(int x);
      void          setsizey(int y);
      void          save(void);
      int*          getlocation(void);
    private:
      int           location[2];
      int           size[2];
  };

    
#endif
