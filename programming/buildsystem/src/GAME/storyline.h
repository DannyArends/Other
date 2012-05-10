/**
 * \file GAME/storyline.h
 * \brief Header file, for GAME/storyline.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef STORYLINE_H_
  #define STORYLINE_H_
  #include "GAME.h"

  /**
  * \brief The storyline class.<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class storyline : public gameobject{
    public:
      storyline();
      ~storyline();

    private:
      vector<user*>       storyplayers;
      vector<gameevent*>  storyevents;
  };

#endif /* STORYLINE_H_ */
