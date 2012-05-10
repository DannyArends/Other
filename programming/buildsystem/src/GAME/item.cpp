/**
 * \file GAME/item.cpp
 * \brief Code file, Implementation of class: \ref item
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "item.h"

item::item(string name,string creator): gameobject::gameobject() {
  this->name=name;
  this->creatorname=creator;
  this->ownername=creator;
  this->description= name + " made by " + creator;
  this->quantity=0;
  this->addchild(new itemattributes());
  this->addchild(new userlevels());
  this->initdb();
}

string item::getname(){
  return this->name;
}

bool item::load(void){
  vector<string> values = this->getrow(this->getobjectname(),this->getid());
  if(values.size()==0) return false;
  this->setid(atoi(values[0].c_str())); //TODO: Remove because its not really needed
  this->name=values[1];
  this->creatorname=values[2];
  this->ownername=values[3];
  this->description=values[4];
  this->quantity=(userstates)atoi(values[5].c_str());
  return true;
}

string item::getownername(){
  return this->ownername;
}

string item::getcreatorname(){
  return this->creatorname;
}

uint item::getquantity(){
  return this->quantity;
}

void item::addquantity(uint i){
  this->quantity += i;
}

uint item::substractquantity(uint i){
  uint took=0;
  if(this->quantity >= i){
    took = i;
    this->quantity -= i;
  }else{
    took = this->quantity;
    this->quantity=0;
  }
  return took;
}

vector<string> item::decomposestructs(){
  vector<string> structs;
  structs.push_back(getobjectname() + "id");
  structs.push_back("name");
  structs.push_back("owner");
  structs.push_back("creator");
  structs.push_back("description");
  structs.push_back("quantity");
  return structs;
}

vector<string> item::decomposetypes(){
  vector<string> types;
  types.push_back("INTEGER PRIMARY KEY");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("INTEGER");
  return types;
}

vector<string> item::decomposevalues(){
  vector<string> values;
  stringstream oss;
  values.push_back(uinttostring(this->getid()));
  values.push_back(this->name);
  values.push_back(this->ownername);
  values.push_back(this->creatorname);
  values.push_back(this->description);
  values.push_back(uinttostring(this->quantity));
  return values;
}

string item::getobjectname(){
  return (string)"item";
}

item::~item() {
  // TODO Destructor code
}
