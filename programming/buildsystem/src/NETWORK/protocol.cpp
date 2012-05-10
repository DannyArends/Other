/**
 * \file NETWORK/protocol.cpp
 * \brief Code file, Implementation of class: \ref protocol
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "protocol.h"

vector<string> tokenize(const string& str, const string& delim){
  using namespace std;
  vector<string> tokens;

  size_t p0 = 0, p1 = string::npos;
  while(p0 != string::npos){
    p1 = str.find_first_of(delim, p0);
    if(p1 != p0){
      string token = str.substr(p0, p1 - p0);
      tokens.push_back(token);
    }
    p0 = str.find_first_not_of(delim, p1);
  }
  return tokens;
}

clientfunction_entry toserverlookup[] = {
         {UPING,      receivedbyserver::c_ping},
         {UCREATE,    receivedbyserver::c_create},
         {ULOGIN,     receivedbyserver::c_login},
         {UlOGOUT,    receivedbyserver::c_logout},
         {UCHAT,      receivedbyserver::c_chat},
         {UMOVE,      receivedbyserver::c_cmd},
};

serverfunction_entry toclientlookup[] = {
         {SPONG,      receivedbyclient::s_pong},
         {SCREATE,    receivedbyclient::s_create},
         {SLOGIN,     receivedbyclient::s_login},
         {SlOGOUT,    receivedbyclient::s_logout},
         {SCHAT,      receivedbyclient::s_chat},
         {SMOVE,      receivedbyclient::s_cmd},
};

void receivedbyserver::c_ping(int clientid){

}

void receivedbyserver::c_create(int clientid){

}

void receivedbyserver::c_login(int clientid){

}

void receivedbyserver::c_logout(int clientid){

}

void receivedbyserver::c_chat(int clientid){

}

void receivedbyserver::c_cmd(int clientid){

}

void receivedbyclient::s_pong(int clientid){

}

void receivedbyclient::s_create(int clientid){

}

void receivedbyclient::s_login(int clientid){

}

void receivedbyclient::s_logout(int clientid){

}

void receivedbyclient::s_chat(int clientid){

}

void receivedbyclient::s_cmd(int clientid){

}

void protocol::processTextCommandToServer(string command, clientinfo* client){
  vector<string> tokens = tokenize(command,":");
  if(tokens[0]=="create"){
    if(tokens.size()==3){
      if(client->gameserver->createuser(tokens[1],tokens[2])){
        client->networkserver->sendcommand("create:ok:",client->clienthostname);
      }else{
        client->networkserver->sendcommand("create:failed:",client->clienthostname);
      }
    }
  }
  if(tokens[0]=="login"){
    if(tokens.size()==3){
      if(client->gameserver->loginuser(tokens[1],tokens[2])){
        client->networkserver->sendcommand("login:ok:",client->clienthostname);
      }else{
        client->networkserver->sendcommand("login:failed:",client->clienthostname);
      }
    }
  }
}

void protocol::processTextCommandFromServer(string command, application* e){
  string protocoldelim = ":";
  //split into tokens and execute command
  vector<string> tokens = tokenize(command, protocoldelim);
  if(tokens[0]=="time"){
    if(tokens.size()==5){
      cout << "[PROTOCOL]\tValid timestamp from server" << endl;
      //TODO: Update the time widget
    }else{
      cerr << "[PROTOCOL]\tInvalid timestamp from server" << endl;
    }
  }
  if(tokens[0]=="create"){
    if(tokens.size()==2){
      cout << "[PROTOCOL]\tCreate: " << tokens[1] << " from server"<< endl;
      //TODO: Handle the creation in the client
    }else{
      cerr << "[PROTOCOL]\tInvalid create message from server" << endl;
    }
  }
  if(tokens[0]=="login"){
    if(tokens.size()==2){
      cout << "[PROTOCOL]\tLogin: " << tokens[1] << " from server"<< endl;
      //TODO: Handle the login in the client
    }else{
      cerr << "[PROTOCOL]\tInvalid login message from server" << endl;
    }
  }
  if(tokens[0]=="add"){
    if(tokens.size()==2){
      cout << "[PROTOCOL]\tAdd server/world/object/npc/user/object/world from server"<< endl;
      //TODO: Handle the add of the thing in the client
    }else{
      cerr << "[PROTOCOL]\tInvalid add message from server" << endl;
    }
  }
  if(tokens[0]=="move"){
    if(tokens.size()==2){
      cout << "[PROTOCOL]\tMove object from server"<< endl;
      //TODO: Handle the login in the client
    }else{
      cerr << "[PROTOCOL]\tInvalid move message from server" << endl;
    }
  }
}


