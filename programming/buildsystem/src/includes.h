/**
 * \file includes.h
 * \brief Header file, containing main c and c++ includes used everywhere
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
#ifndef INCLUDES_H_
  #define INCLUDES_H_
  
  #include "basicincludes.h"
  #include <assert.h>
  #include <stdarg.h>
  #include <dirent.h>
  #include "config.h"
  

  #ifdef WINDOWS
    #include <windows.h>
    #undef ERROR
    #define sleep(n) {\
      Sleep(n);\
    }
  #endif

  /**
   * \brief Class, All classes should inherit from this one.<br>
   *
   *  Provides identification classes, inherited by all other object classes like:
   *  - \ref object2d Class providing basic interface for all 2D objects
   *  - \ref object3d Class providing basic interface for all 3D objects
   *  - \ref gameobject Class providing basic interface for all game objects
   *  - \ref networkobject Class providing basic interface for all network objects
   *  - \ref mathobject Class providing basic interface for all mathematical objects
   * TODO Description<br>
   * bugs: none found<br>
   */
  class object{
    public:
      object(){this->id=0;}
      object(uint id){this->id=id;}
      uint getid(void){return this->id;}
      void setid(uint id){this->id = id;}
      ~object(){};
    private:
      uint id;
  };

  #include "BASE/BASE.h"

#endif
