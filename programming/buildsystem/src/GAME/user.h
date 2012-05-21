/**
 * \file GAME/user.h
 * \brief Header file, for GAME/user.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef USER_H_
  #define USER_H_
  #include "GAME.h"

  /** 
  * \brief Representation of a user
  */
  class user: public gameobject{
    public:
      user();
      user(string name,string pass);
      bool            load(void);
      string          getobjectname();
      ~user();
    private:
     vector<string>   decomposestructs();
     vector<string>   decomposetypes();
     vector<string>   decomposevalues();
     string           name;           //Name of user
     string           password;       //Password of user
     string           home;           //Map of user
     userstates       state;          //User state
     string           description;    //Users own description

  };

#endif
