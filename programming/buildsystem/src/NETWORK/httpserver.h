/**
 * \file NETWORK/httpserver.h
 * \brief Header file, for NETWORK/httpserver.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef HTTPSERVER_H_
  #define HTTPSERVER_H_
  #include "NETWORK.h"
  
  
  #define SERVER_NAME	"WebInterface"

  #define ERROR_400	"<html><head><title>400</title></head><body><h1>Error 400</h1><p>The server couldn't understand your request.</body></html>\n"
  #define ERROR_404	"<html><head><title>404</title></head><body><h1>Error 404</h1><p>Document %s not found.</body></html>\n"
  #define HOME_PAGE	"<html><head><title>Home</title></head><body><h1>Home</h1><p>Homepage.</p></body></html>\n"
  #define TIME_PAGE	"<html><head><title>Time</title></head><body><html><h1>Time</h1><p>The current date is: %s</p></body></html>\n"
  
  /** 
    * \brief The httpserver class lauches a thread to monitor incomming connections on port 80<br>
    *
    * TODO Description<br>
    * bugs: none found
    */
  class httpserver : public networkobject{
    public:
      httpserver(sdlserverstruct* application);
      ~httpserver();
    private:
      mythread sdlthread;
  };

#endif
