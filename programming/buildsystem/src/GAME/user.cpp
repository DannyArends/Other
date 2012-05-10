/**
 * \file GAME/user.cpp
 * \brief Code file, Implementation of class: \ref user
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#include "user.h"

/**
* \brief The user class<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
user::user() : gameobject::gameobject(){
  this->state=UNDEFINED;
}

user::user(string name, string pass) : gameobject::gameobject(){
  this->name=name;
  this->password=pass;
  this->home=name;
  this->state=UNDEFINED;
  this->description="No description yet";
  this->addchild(new userlevels());
  this->addchild(new userattributes());
  this->addchild(new usernexus());
  this->addchild(new userlooks());
  this->addchild(new usergear());
  this->initdb();
}

/**
* \brief The user class destructor<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
user::~user(){

}

bool user::load(void){
  vector<string> values = this->getrow(this->getobjectname(),this->getid());
  if(values.size()==0) return false;
  this->setid(atoi(values[0].c_str())); //TODO: Remove because its not really needed
  this->name=values[1];
  this->password=values[2];
  this->home=values[3];
  this->state=(userstates)atoi(values[4].c_str());
  this->description=values[5];
  return true;
}

vector<string> user::decomposestructs(){
  vector<string> structs;
  structs.push_back(getobjectname() + "id");
  structs.push_back("name");
  structs.push_back("password");
  structs.push_back("home");
  structs.push_back("state");
  structs.push_back("description");
  return structs;
}

vector<string> user::decomposetypes(){
  vector<string> types;
  types.push_back("INTEGER PRIMARY KEY");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("STRING");
  types.push_back("INTEGER");
  types.push_back("STRING");
  return types;
}

vector<string> user::decomposevalues(){
  vector<string> values;
  values.push_back(uinttostring(this->getid()));
  values.push_back(this->name);
  values.push_back(this->password);
  values.push_back(this->home);
  values.push_back(uinttostring(this->state));
  values.push_back(this->description);
  return values;
}

string user::getobjectname(){
  return (string)"user";
}


