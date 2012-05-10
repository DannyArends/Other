/**
 * \file NETWORK/cloudmember.cpp
 * \brief Code file, Implementation of class: \ref cloudmember
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "cloudmember.h"

cloudmember::cloudmember(sdlserverstruct* app) {
  this->myapplication = app;
  // TODO Constructor code
}

/**
 * \brief Starts up a cloud and tries to connect to known cloud servers<br>
 *
 * bugs: none found
 * @param serverfilepath The location on disk with the servers<br>
 */
void cloudmember::startcloud(string serverfilepath){
  string line;
  cout << "[CLOUD]\t\tStarting cloud using server list at: " + serverfilepath << endl;
  ifstream myfile(serverfilepath.c_str());
  if (myfile.is_open()){
    while (! myfile.eof() ){
      getline (myfile,line);
      addtocloud(line);
    }
    myfile.close();
  }
}

/**
 * \brief Add a new server to the cloud<br>
 *
 * bugs: none found
 * @param targetadres The http location of the server<br>
 */
void cloudmember::addtocloud(string targetadres){
  if(targetadres=="") return;
  bool found = false;
  for(uint t=0;t<this->getchildren().size();t++){
    if(this->getchildren()[t]->gethostname()==targetadres) found=true;
  }
  if(!found){
    cout << "[CLOUD]\t\t'" << targetadres << "' not in cloud, going to add" << endl;
    sdlclient* s = new sdlclient(this->myapplication,targetadres);
    this->addchild(s);
  }else{
    cout << "[CLOUD]\t\t'" << targetadres << "' already in cloud" << endl;
  }
}

/**
 * \brief Remove an inactive server from the cloud<br>
 *
 * bugs: none found
 * @param targetadres The http location of the server<br>
 */
void cloudmember::removefromcloud(string targetadres){
  bool found = false;
  for(uint t=0;t<this->getchildren().size();t++){
    if(this->getchildren()[t]->gethostname()==targetadres){
      this->removechild(t);
      cout << "[CLOUD]\t\tRemoved server: " +targetadres << endl;
      found=true;
    }
  }
  if(!found){
    cout << "[CLOUD]\t\tFailed to remove server: " << targetadres << endl;
  }
}

/**
 * \brief Send a command to all known cloud servers<br>
 *
 * bugs: none found
 * @param command string command to send<br>
 */
void cloudmember::sendcommand(string command){
  uint cnt=0;
  for(uint t=0;t<this->getchildren().size();t++){
    this->getchildren()[t]->sendcommand(command);
    if(this->getchildren()[t]->gethoststatus()) cnt++;
  }
  cout << "[CLOUD]\t\tCommand '"<< command <<"' send to " << cnt << "/" <<this->getchildren().size()<<" server(s)" << endl;
}


cloudmember::~cloudmember() {
  // TODO Destructor code
}
