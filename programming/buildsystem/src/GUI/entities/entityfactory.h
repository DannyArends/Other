/**
 * \file GUI/entities/entityfactory.h
 * \brief Header file, for GUI/entities/entityfactory.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef ENTITYFACTORY_H_
  #define ENTITYFACTORY_H_
  #include "ENTITIES.h"
  
  /** 
  * \brief Factory class for creating and managing all entities.
  */
  class entityfactory: public node<entity>{
  public:
         entityfactory(universe* u);
    bool loadlocal3ds(void);
    bool loadlocalmaps(void);
    bool loadremoteentities(void);
         ~entityfactory(void);
  private:
    universe* myuniverse;
  };

#endif
