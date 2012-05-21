/**
 * \file GAME/storage.cpp
 * \brief Code file, Implementation of class: \ref storage
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "storage.h"

storage::storage(): gameobject::gameobject(){
  // TODO Constructor code

}

bool storage::storeitem(item* i){
 bool found = false;
    for(uint x=0;x<this->items.size() && !found;x++){
    if(this->items[x]->getid()==i->getid()){
      cout << "QTY of item stored "<< i->getname() <<" created by "<< i->getcreatorname() << ":" << this->items[x]->getquantity() << "+" << i->getquantity() << "=";
      this->items[x]->addquantity(i->getquantity());
      cout << "=" + this->items[x]->getquantity() << endl;
      found=true;
    }
  }
  if(!found){
    this->items.push_back(i);
    cout << "New item stored "<<i->getname()<<" created by "<<i->getcreatorname()<<": "<<i->getquantity()<<" qty" << endl;
  }
  return found;
}

item* storage::retrieveitem(uint id, uint qty){
  bool found = false;
  item* returnitem = new item("","");
  for(uint x=0;x<this->items.size() && !found;x++){
    if(this->items[x]->getid()==id){
      cout << "Found "<<this->items[x]->getname()<<" created by " << this->items[x]->getcreatorname() << endl;
      returnitem = this->items[x];
      returnitem->addquantity(this->items[x]->substractquantity(qty));
      cout << "Now left with " << this->items[x]->getquantity() << "items" << endl;
      found=true;
    }
  }
  if(!found){
    cout << "No such item in storage" << endl;
    returnitem=NULL;
  }
  return returnitem;
}

storage::~storage() {
  // TODO Destructor code
}
