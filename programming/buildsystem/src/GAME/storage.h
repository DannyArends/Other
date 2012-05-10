/**
 * \file GAME/storage.h
 * \brief Header file, for GAME/storage.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef STORAGE_H_
#define STORAGE_H_
  #include "GAME.h"

  /**
  * \brief Virtual storage class holding game objects in a container like fashion
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class storage : public gameobject {
    public:
              storage();
      bool    storeitem(item* i);
      item*   retrieveitem(uint id, uint qty);
              ~storage();
      vector<item*>  items;
    private:

  };

#endif /* STORAGE_H_ */
