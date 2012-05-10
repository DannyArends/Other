/**
 * \file MYMATH/MYMATH.h
 * \brief Header file, for the MYMATH directory
 *
 * This class is used to share the objects within the MYMATH directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef MYMATH_H_
  #define MYMATH_H_
  #include "includes.h"

  /**
  * \brief Empty superclass class of math objects
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class mathobject : public object{
    public:
      mathobject():object::object(){

      }
      ~mathobject(){

      }
    private:
  };
  
  //Share the objects
  #include "biology.h"
  #include "compartiment.h"
  #include "curve.h"
  #include "geneticalgorithm.h"
  #include "pathfinding.h"
  #include "population.h"
  #include "regression.h"
  

#endif
