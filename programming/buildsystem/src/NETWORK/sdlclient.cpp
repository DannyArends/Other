/**
 * \file NETWORK/sdlclient.cpp
 * \brief Code file, Implementation of class: \ref sdlclient
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
#include "sdlclient.h"

void* startclient(void* ptr);

sdlclient::sdlclient(sdlserverstruct* appdata, string hostname){
  cout << "[STARTUP]\tSDLclient for '" << hostname << "'" << endl;
  this->parentapplication = appdata;
  this->hostname=hostname;
  this->command="HELLOW anyone there?";
  this->outflag=true;
  this->inflag=false;
  clearlinebuffer();
  this->sdlthread.rvalue = (int)pthread_create(&sdlthread.thread, NULL, startclient, (void*) this);
}

sdlserverstruct* sdlclient::getapplication(void){
 return this->parentapplication;
}

void sdlclient::sendcommand(string command){
  this->command=command;
  this->outflag=true;
}

void sdlclient::clearlinebuffer(void){
  for(uint x=0;x<BUFFER1024;x++){
  this->linebuffer[x] = ' ';
  }
}

void sdlclient::sethostname(string hostname){
  this->hostname=hostname;
}

string sdlclient::getcommand(void){
  return this->command;
}

string sdlclient::gethostname(void){
  return this->hostname;
}

void sdlclient::setoutflag(bool cmdflag){
  this->outflag=cmdflag;
}

bool sdlclient::getoutflag(void){
  return this->outflag;
}

void sdlclient::setinflag(bool cmdflag){
  if(!cmdflag) clearlinebuffer();
  this->inflag=cmdflag;
}

string sdlclient::getlinebuffer(void){
  return string(this->linebuffer);
}

bool sdlclient::getinflag(void){
  return this->inflag;
}

bool sdlclient::gethoststatus(void){
  return this->hostonline;
}

void sdlclient::sethoststatus(bool status){
  this->hostonline = status;
}

void* startclient(void* ptr){
  sdlclient* clientapp = (sdlclient*)ptr;
  // Create a socket set to handle up to 16 sockets
  SDLNet_SocketSet set;
  TCPsocket     socket;
  string        buffer;
  IPaddress*    ip = new IPaddress();
  int           len=0;
  int           numready=-1;
  clientapp->sethoststatus(false);
  if (SDLNet_Init() < 0){
    cerr << "[SDLCLIENT]\t SDL_Net not running" << endl;
    sleep(clientapp->getapplication()->serverpoll);
    startclient(clientapp);
  }
  if (SDLNet_ResolveHost(ip, clientapp->gethostname().c_str(), 2000) < 0){
    cerr << "[SDLCLIENT]\terror resolving: " << SDLNet_GetError() << endl;
    sleep(clientapp->getapplication()->serverpoll);
    startclient(clientapp);
  }
  if (!(socket = SDLNet_TCP_Open(ip))){
    cerr << "[SDLCLIENT]\terror opening: " << SDLNet_GetError() << endl;
    sleep(clientapp->getapplication()->serverpoll);
    startclient(clientapp);
  }

  set = SDLNet_AllocSocketSet(1);
  if (!set) { cerr << "SDLNet_AllocSocketSet: " << SDLNet_GetError() << endl; }
  if (SDLNet_TCP_AddSocket(set, socket) == -1) {
    cerr << "[SDLCLIENT]\tSDLNet_AddSocket error: " << SDLNet_GetError() << endl;
    sleep(clientapp->getapplication()->serverpoll);
    SDLNet_FreeSocketSet(set);
    startclient(clientapp);
  }else{
    clientapp->sethostname(SDLNet_ResolveIP(ip));
    cout << "[SDLCLIENT]\tConnected to '"<< clientapp->gethostname() <<"' on port: 2000" << endl;
    clientapp->sethoststatus(true);
  }
  while(clientapp->getapplication()->running && clientapp->gethoststatus()){
    if(clientapp->getoutflag()){
      buffer  = clientapp->getcommand();
      len     = buffer.size() + 1;
      if (SDLNet_TCP_Send(socket, (void *)buffer.c_str(), len) < len){
        message("[SDLCLIENT]\tError: Server connection lost, no reason for this SDL client to live anymore\n");
        clientapp->sethoststatus(false);
      }else{
        clientapp->setoutflag(false);
      }
    }else{
      numready = SDLNet_CheckSockets(set, 25);
      if (numready > 0 && SDLNet_SocketReady(socket)) {
        if (numready == -1) {
            cerr << "[SDLCLIENT]\tSDLNet_CheckSockets: " << SDLNet_GetError() << endl;
        }
        if ((clientapp->commandlength = SDLNet_TCP_Recv(socket, clientapp->linebuffer, BUFFER1024)) > 0){
          //cout << "[SDLCLIENT]\tMSG:"<<clientapp->commandlength<<": "<< clientapp->linebuffer <<" from server " << clientapp->gethostname() << endl;
          clientapp->setinflag(true);
        }else{
          cerr << "[SDLCLIENT]\tConnection failure to: " << clientapp->gethostname() << endl;
          clientapp->sethoststatus(false);
        }
      }
      sleep(25);
    }
	}

	SDLNet_TCP_Close(socket);
	if(clientapp->getapplication()->running){
	  cerr << "[SDLCLIENT]\tExit" <<endl;
	  sleep(clientapp->getapplication()->serverpoll);
	  SDLNet_FreeSocketSet(set);
	  cout << "[SDLCLIENT]\tRecovering from connection error to server" << endl;
	  startclient(clientapp);
	}else{
    SDLNet_FreeSocketSet(set);
	  cout << "[SDLCLIENT]\tExit" <<endl;
	}
  pthread_exit((void*) 0);
  return((void*) 0);
}
