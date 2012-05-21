/**
 * \file GAME/world.h
 * \brief Header file, for GAME/world.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef WORLD_H_
  #define WORLD_H_
  #include "GAME.h"
  
  /** 
  * \brief Representation of a gameworld<br>
  *
  * TODO Documentation<br>
  * bugs: none found<br>
  */
  class world : public gameobject{
    public:
      world(string name,string creator);
      ~world();
    private:
      virtual vector<string>   decomposestructs();
      virtual vector<string>   decomposetypes();
      virtual vector<string>   decomposevalues();
      virtual string           getobjectname();
      string                name;               //Name of the item
      string                creatorname;        //Name of item creator
      string                description;       //Item description
      vector<user*>         users;
      vector<gameobject*>   objects;
      vector<npc*>          npcs;
      vector<storage*>      containers;
  };

#endif
