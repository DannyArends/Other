/**
 * \file GAME/GAME.h
 * \brief Header file, for the GAME directory
 *
 * This class is used to share the objects within the GAME directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * - \ref gameevent<br>
 * - \ref item<br>
 * - \ref npc<br>
 * - \ref gameobject<br>
 * - \ref storage<br>
 * - \ref storyline<br>
 * - \ref user<br>
 * - \ref world<br>
 *
 **/

#ifndef GAME_H_
  #define GAME_H_
  #include "includes.h"
  #include "GAMEstructures.h"

  //ALL DEPENDENCIES FOR THIS LIBRARY
  
  /**
   * \brief Locations of all gameobjects
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class gameobjectlocation : public object3d, public databaseobject{
    public:
      gameobjectlocation() : object3d::object3d(),databaseobject::databaseobject(){
        this->initdb();
      }
      string           getobjectname(){ return "gameobjectlocation"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setlocation(atof(values[2].c_str()), atof(values[3].c_str()),atof(values[4].c_str()));
        return true;
      }
      ~gameobjectlocation(){ }
    private:
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        structs.push_back("name");
        structs.push_back("xloc");
        structs.push_back("yloc");
        structs.push_back("zloc");
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        types.push_back("STRING");
        types.push_back("REAL");
        types.push_back("REAL");
        types.push_back("REAL");
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        values.push_back(this->getparent()->getobjectname());
        values.push_back(uinttostring(this->getx()));
        values.push_back(uinttostring(this->gety()));
        values.push_back(uinttostring(this->getz()));
        return values;
      }
  };

  /**
   * \brief Empty superclass of all game objects
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class gameobject : public databaseobject{
    public:
      gameobject() : databaseobject::databaseobject(){
        this->addchild(new gameobjectlocation());
        this->initdb();
      }
      string           getobjectname(){ return "gameobject"; }
      ~gameobject(){ }
    private:
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        structs.push_back("name");
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        types.push_back("STRING");
        return types;
      };
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getid()));
        values.push_back(getobjectname() + uinttostring(this->getid()));
        return values;
      };
  };
  class gameengine;
  class gameevent;
  class item;
  class npc;
  class storage;
  class storyline;
  class user;
  class world;

  #include "gameengine.h"
  #include "gameevent.h"
  #include "item.h"
  #include "npc.h"
  #include "storage.h"
  #include "storyline.h"
  #include "user.h"
  #include "world.h"

#endif
