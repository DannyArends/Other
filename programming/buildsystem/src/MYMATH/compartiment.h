/**
 * \file MYMATH/compartiment.h
 * \brief Header file, for MYMATH/compartiment.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef COMPARTIMENT_H_
  #define COMPARTIMENT_H_
  
  #include "MYMATH.h"
   /** 
        * \brief Compartiment is an concept class, it is formed from other classes
        * bugs: none found
        */
  class compartiment : public mathobject{
    public:
      compartiment();
      ~compartiment();
      
    private:
      vector<object3d*>      content;
      vector<compartiment*>  subcompartiments;
  };

#endif
