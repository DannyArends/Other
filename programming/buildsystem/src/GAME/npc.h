/**
 * \file GAME/npc.h
 * \brief Header file, for GAME/npc.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef NPC_H_
  #define NPC_H_
  #include "GAME.h"
  
  /** 
      * \brief Representation of an npc
      */
  class npc:public gameobject{
    public:
      npc();
    private:
      npctypes            type;
      vector<gameevent*>  events;
  };

#endif
