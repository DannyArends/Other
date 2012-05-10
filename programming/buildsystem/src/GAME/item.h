/**
 * \file GAME/item.h
 * \brief Header file, for GAME/item.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef ITEM_H_
  #define ITEM_H_
  #include "GAME.h"

  /**
  * \brief Class for game items like reagents and resources.<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class item : public gameobject{
    public:
      item(string name,string creator);
      string           getname();
      bool             load(void);
      string           getownername();
      string           getcreatorname();
      uint             getquantity();
      void             addquantity(uint i);
      uint             substractquantity(uint i);
      string           getobjectname();
      ~item();
    private:
      string           name;              //Name of the item
      string           ownername;         //Name of the current owner
      string           creatorname;       //Name of item creator
      string           description;       //Item description
      uint             quantity;          //Item quantity
      vector<string>   decomposestructs();
      vector<string>   decomposetypes();
      vector<string>   decomposevalues();
  };

#endif /* ITEM_H_ */
