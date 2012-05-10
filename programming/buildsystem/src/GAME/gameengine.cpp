/**
 * \file GAME/gameengine.cpp
 * \brief Code file, Implementation of class: \ref gameengine
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "gameengine.h"

/**
* \brief The game engine class constructor<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
gameengine::gameengine() : database::database(){

}

bool gameengine::createuser(string name,string password){
  if(!this->keyexists("user","name",name)){
    user* aspuser = new user(name,password);
    aspuser->save();
    this->users.push_back(aspuser);
    return true;
  }else{
    cerr << "[GAME]\tUsername: " << name << " already in database" << endl;
  }
  return false;
}

bool gameengine::loginuser(string name,string password){
  if(this->keyexists("user","name",name)){
    if(this->getdatafield("user","name",this->idofkey("user","name",name))==password){
      cout << "[GAME]\tLogin of user: " << name << endl;
      user* aspuser = new user();
      aspuser->setid(this->idofkey("user","name",name));
      aspuser->load();
      this->users.push_back(aspuser);
      return true;
    }else{
      cerr << "[GAME]\tLogin of user: " << name << "failed due to password error" << endl;
    }
  }else{
    cerr << "[GAME]\tLogin of unknown user: " << name << endl;
  }
  return false;
}

/**
* \brief The game engine class destructor<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
gameengine::~gameengine(){

}
