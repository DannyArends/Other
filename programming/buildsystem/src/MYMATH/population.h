/**
 * \file MYMATH/population.h
 * \brief Header file, for MYMATH/population.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef POPULATION_H_
  #define POPULATION_H_
  
  #include "MYMATH.h"
   
 /** 
      * \brief Represent a genetic marker.
      *
      * bugs: none found
      */
  struct marker{
    int    bp;
    float  cm,lod;
    char   value;
  };
  
 /** 
      * \brief Represent a genetic linkage group (chromosome).
      *
      * bugs: none found
      */  
  struct linkagegroup{
    marker* markers;
    bool    autosome;
  };
  
 /** 
      * \brief Represent a hetrozygote recombinant.
      *
      * bugs: none found
      */    
  class recombinant : public mathobject{
  public:
  	recombinant(void);
  	~recombinant(void);
  private:
    vector<double*>        traits;
    vector<linkagegroup*>  chromosomes;
  };

 /** 
      * \brief Population of recombinants.
      *
      * bugs: none found
      */ 
  class population : public mathobject{
  public:
  	population(void);
  	~population(void);
    bool loadfromfile(string filename);
    void save(void);
  private:
    vector<recombinant*> rils;
  };

#endif
