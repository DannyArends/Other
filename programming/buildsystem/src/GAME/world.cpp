/**
 * \file GAME/world.cpp
 * \brief Code file, Implementation of class: \ref world
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "world.h"

/**
* \brief The world class constructor<br>
*
* TODO Description and Code
* bugs: none found<br>
*/
world::world(string name,string creator) : gameobject::gameobject(){
  this->name=name;
  this->creatorname=creator;
  this->description="World created by: " + creator;
}

vector<string> world::decomposestructs(){
  vector<string> structs;
  structs.push_back(getobjectname() + "id");
  structs.push_back("name");
  structs.push_back("creator");
  structs.push_back("description");
  return structs;
}

vector<string> world::decomposetypes(){
  vector<string> types;
  types.push_back("INTEGER PRIMARY KEY");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("STRING");
  return types;
}

vector<string> world::decomposevalues(){
  vector<string> values;
  stringstream oss;
  values.push_back(uinttostring(this->getid()));
  values.push_back(this->name);
  values.push_back(this->creatorname);
  values.push_back(this->description);
  return values;
}

string world::getobjectname(){
  return (string)"item";
}

/**
* \brief The world class destructor<br>
*
* TODO Description and Code
* bugs: none found<br>
*/
world::~world(){

}
