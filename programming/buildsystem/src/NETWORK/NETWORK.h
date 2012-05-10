/**
 * \file NETWORK/NETWORK.h
 * \brief Header file, for the NETWORK directory
 *
 * This class is used to share the objects within the NETWORK directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef NETWORK_H_
  #define NETWORK_H_
  
  #include "includes.h"
  #include "application.h"
  #include "THREADING/THREADING.h"
  #include "GAME/GAME.h"
  #include "GUI/GUI.h"
//ALL DEPENDENCIES FOR THIS LIBRARY
  #ifdef WINDOWS
    #include <pthread/pthread.h>    /* POSIX Threads for windows */
  #endif

  #include <SDL/SDL.h>
  #include <SDL/SDL_net.h>
  
  const uint numberofclients = 100;

  class cloudmember;
  class httpserver;
  class sdlclient;
  class sdlserver;
  class protocol;
  class receivedbyserver;
  class receivedbyclient;
  
  /**
   * \brief Structure for pthread information
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct mythread{
    pthread_t   thread;
    int         done;
    int         rvalue;
  } mythread;
  
  /**
   * \brief Structure holding client information
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
   typedef struct clientinfo{
    string      clienthostname;
    mythread    thread;
    TCPsocket*  clientsocket;
    IPaddress*  remoteIP;
    bool        online;
    char        linebuffer[BUFFER1024];
    gameengine* gameserver;
    sdlserver*  networkserver;
  }clientinfo;
  
  /**
   * \brief Structure application information
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct sdlserverstruct{
    bool                 running;          //Are we running ???
    string               serverfile;       //Were are we storing the servers
    uint                 serverpoll;       //How often to bother them ?
    TCPsocket            serversocket;     //Server socket
    IPaddress            ip;               //Server IP
    timeserver*          ourtime;          //Pointer to the applications timeserver
    vector<clientinfo*>  clients;          //Clients to this server
  }sdlserverstruct;
  
  /**
   * \brief Empty superclass class of networks objects
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class networkobject : public object{
    public:
      networkobject():object::object(){

      }
      ~networkobject(){

      }
    private:
  };


  #include "protocol.h"
  #include "cloudmember.h"
  #include "httpserver.h"
  #include "sdlclient.h"
  #include "sdlserver.h"

#endif
