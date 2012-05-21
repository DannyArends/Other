/**
 * \file NETWORK/sdlserver.cpp
 * \brief Code file, Implementation of class: \ref sdlserver
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "sdlserver.h"

/*
 * \brief Starts a detached sdl client handler, that only knows \ref clientinfo struct
 *
 */
void* sdlclienthandler(void* ptr){
  clientinfo* client = (clientinfo*)ptr;
  while (client->online){
    if (SDLNet_TCP_Recv(*client->clientsocket, client->linebuffer, BUFFER1024) > 0){
      cout << "[SDLCLIENT]\tid: " << SDLNet_ResolveIP(client->remoteIP) << " " << client->remoteIP->port <<"\t:" << client->linebuffer << endl;
      if(strcmp(client->linebuffer, "exit") == 0){
        client->online = false;
      }
      receivedbyserver* p = new receivedbyserver();
      p->processTextCommandToServer(client->linebuffer,client);
    }else{
      client->online = false;
    }
  }
  cout << "[HOST]\t\tDown " << SDLNet_ResolveIP(client->remoteIP) << " " << client->remoteIP->port << endl;
  SDLNet_TCP_Close(*client->clientsocket);
  pthread_exit((void*) 0);
  return((void*) 0);
}

/*
 * \brief Starts a detached sdl server, that only knows \ref sdlserver class
 *
 */
void* startsdlserver(void* ptr){
  sdlserver* master = (sdlserver*)ptr;
  sdlserverstruct* application = master->getapplication();
	if (SDLNet_Init() < 0){
    cerr << "[SDLSERVER]\terror sdl init: " << SDLNet_GetError() << endl;
    master->setserving(false);
    pthread_exit((void*) 0);
  }
	if (SDLNet_ResolveHost(&application->ip, NULL, 2000) < 0){
    cerr << "[SDLSERVER]\terror resolving: " << SDLNet_GetError() << endl;
    master->setserving(false);
    pthread_exit((void*) 0);
  }
	if (!(application->serversocket = SDLNet_TCP_Open(&application->ip))){
    cerr << "[SDLSERVER]\terror opening: " << SDLNet_GetError() << endl;
    master->setserving(false);
    pthread_exit((void*) 0);
  }
  cout << "[SDLSERVER]\tMonitoring for clients on port: 2000" << endl;
  while(application->running){
    sleep(20);
    TCPsocket temp = SDLNet_TCP_Accept(application->serversocket);

	  if(temp > 0){
	    mythread newconnection;
	    clientinfo* ci = new clientinfo();
	    ci->clientsocket =  new TCPsocket(temp);
	    if((ci->remoteIP = SDLNet_TCP_GetPeerAddress(*ci->clientsocket))){
	      ci->online = true;
	      SDLNet_Read32(&ci->remoteIP->host);
	      SDLNet_Read16(&ci->remoteIP->port);
	      cout << "[HOST]\t\t" << SDLNet_ResolveIP(ci->remoteIP) << " " << ci->remoteIP->port << endl;
	      ci->clienthostname=SDLNet_ResolveIP(ci->remoteIP);
	      ci->gameserver=master->getlocalgame();
	      ci->networkserver=master;
	      master->getcloud()->addtocloud(ci->clienthostname);
	      newconnection.rvalue = (int)pthread_create(&newconnection.thread, NULL, sdlclienthandler, (void*) ci);
	      application->clients.push_back(ci);
      }else{
        cout << "[SDL]\t\tError: " << SDLNet_GetError()<<endl;
      }
    }
	}
	SDLNet_TCP_Close(application->serversocket);
	//SDLNet_Quit();
  pthread_exit((void*) 0);
  return((void*) 0);
}

sdlserver::sdlserver(sdlserverstruct* application, configfile* c){
  cout << "[STARTUP]\tSDLserver" << endl;
  this->application=application;
  this->servingclients=true;
  this->setinterval(5);
  this->application->serverfile=c->read<string>("serverfile","servers.lst");
  this->application->serverpoll=c->read<int>("serverpoll",3000);
  this->sdlthread.rvalue = (int)pthread_create(&sdlthread.thread, NULL, startsdlserver, (void*) this);
  cout << "[STARTUP]\tCLOUDserver" << endl;
  this->cloud = new cloudmember(this->application);
  this->localgame = new gameengine();
  cloud->startcloud(c->read<string>("serverfile","servers.lst"));
}

/*
 * \brief Set if we are serving clients
 *
 * @param status Serving yes or no
 */
void sdlserver::setserving(bool status){
  this->servingclients=status;
}

/*
 * \brief Return the clients attached to this server
 *
 * @return Number of clients attached to this server
 */
uint sdlserver::getnumberofclients(void){
  if(!this->servingclients) return 0;
  uint cntonline;
  for(uint x=0;x<this->application->clients.size();x++){
    if(this->application->clients[x]->online) cntonline++;
  }
  message("[SDLSERVER]\t%d/%d clients online\n",cntonline,this->application->clients.size());
  return this->application->clients.size();
}

/*
 * \brief Return the cloudmember attached to this server
 *
 *
 */
cloudmember* sdlserver::getcloud(void){
  return this->cloud;
}

sdlserverstruct* sdlserver::getapplication(){
  return this->application;
}

gameengine* sdlserver::getlocalgame(){
  return this->localgame;
}

/*
 * \brief Inherited from \ref timedobject a task to execute periodically
 *
 *
 */
void sdlserver::timedtask(void){
  if(!this->servingclients) return;

  string s = "time:"+this->application->ourtime->printtime();
  sendcommandall(s);
}

/*
 * \brief Send command to a client
 *
 * @param command Command to send
 * @param hostname hostname used to identify the client
 *
 */
void sdlserver::sendcommand(string command,string hostname){
  if(!this->servingclients) return;
  for(uint x=0;x<this->application->clients.size();x++){
    if(hostname == this->application->clients[x]->clienthostname){
      if(this->application->clients[x]->online){
        message("[SDLSERVER]\tFound %s as active client",hostname.c_str());
        if ((uint)SDLNet_TCP_Send(*this->application->clients[x]->clientsocket, (void *)command.c_str(), command.length()) < command.length()){
          message("[SDLSERVER]\tclient connection lost %s",this->application->clients[x]->clienthostname.c_str());
        }else{
          cout << "[SDLSERVER]\tDeliverd a personal message to"<< hostname << endl;
        }
      }
    }
  }
}

/*
 * \brief Send command to a all clients
 *
 * @param command Command to send
 *
 */
void sdlserver::sendcommandall(string command){
  if(!this->servingclients) return;
  uint cnt=0;
  for(uint x=0;x<this->application->clients.size();x++){
    if(this->application->clients[x]->online){
      if ((uint)SDLNet_TCP_Send(*this->application->clients[x]->clientsocket, (void *)command.c_str(), command.length()) < command.length()){
        message("[SDLSERVER]\tclient connection lost %s",this->application->clients[x]->clienthostname.c_str());
      }else{
        cnt++;
      }
    }
  }
  cout << "[SDLSERVER]\tMessage send to " << cnt << " clients" << endl;
}

sdlserver::~sdlserver(){
  SDLNet_Quit();
}
