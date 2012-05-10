/**
 * \file NETWORK/sdlserver.h
 * \brief Header file, for NETWORK/sdlserver.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
 #ifndef SDLSERVER_H_
  #define SDLSERVER_H_
  #include "NETWORK.h"
  
  /**
  * \brief The sdlserver accepts client connections on port 2000<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class sdlserver : public networkobject, public timedobject{
    public:
      sdlserver(sdlserverstruct* application,configfile* c);
      uint              getnumberofclients(void);
      cloudmember*      getcloud(void);
      sdlserverstruct*  getapplication();
      gameengine*       getlocalgame();
      void              timedtask();
      void              sendcommand(string command,string hostname);
      void              sendcommandall(string command);
      void              setserving(bool status);
      ~sdlserver();
    private:
      bool              servingclients;
      mythread          sdlthread;
      cloudmember*      cloud;
      sdlserverstruct*  application;
      gameengine*       localgame;
  };

#endif
