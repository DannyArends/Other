/**
 * \file NETWORK/sdlclient.h
 * \brief Header file, for NETWORK/sdlclient.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef SDLCLIENT_H_
  #define SDLCLIENT_H_
  #include "NETWORK.h"
  
  /**
   * \brief The sdl client connects to an sdl server on port 2000<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class sdlclient : public networkobject{
    public:
      sdlclient(sdlserverstruct* appdata,string hostname);
      sdlserverstruct* getapplication(void);
      void   sendcommand(string command);
      void   sethostname(string hostname);
      void   setparent(sdlclient* p){ };
      string getcommand(void);
      void   clearlinebuffer(void);
      string getlinebuffer(void);
      string gethostname(void);
      void   setoutflag(bool cmdflag);
      bool   getoutflag(void);
      void   setinflag(bool cmdflag);
      bool   getinflag(void);
      bool   gethoststatus(void);
      void   sethoststatus(bool status);
      char                linebuffer[BUFFER1024];
      int                 commandlength;
    private:
      bool                hostonline;
      string              hostname;
      string              command;
      bool                outflag,inflag;
      sdlserverstruct*    parentapplication;
      mythread            sdlthread;
  };

#endif
