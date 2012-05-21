/**
 * \file NETWORK/cloudmember.h
 * \brief Header file, for NETWORK/cloudmember.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef CLOUDMEMBER_H_
  #define CLOUDMEMBER_H_
  #include "NETWORK.h"

  /**
    * \brief The cloudmember class<br>
    *
    * TODO Description<br>
    * bugs: none found
    */
  class cloudmember:public networkobject,public node<sdlclient>{
    public:
      cloudmember(sdlserverstruct* app);
      void startcloud(string serverfilepath);
      void addtocloud(string targetadres);
      void removefromcloud(string targetadres);
      void sendcommand(string command);
      ~cloudmember();
    private:
      sdlserverstruct* myapplication;
  };

#endif /* CLOUDMEMBER_H_ */
