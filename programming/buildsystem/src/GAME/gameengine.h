/**
 * \file GAME/gameengine.h
 * \brief Header file, for GAME/gameengine.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef GAMEENGINE_H_
  #define GAMEENGINE_H_
  #include "GAME.h"
  
  /** 
      * \brief Monitors gamestate
      */
  class gameengine : public database{
    public:
      gameengine();
      ~gameengine();
      bool createuser(string name,string command);
      bool loginuser(string name,string command);
      void createworld(void);
      void createstory(void);
    private:
      vector<user*>       users;
  };

#endif
