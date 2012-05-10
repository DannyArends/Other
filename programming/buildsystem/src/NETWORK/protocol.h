/**
 * \file NETWORK/protocol.h
 * \brief Header file, contains protocol definitions for communication
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef PROTOCOL_H_
  #define PROTOCOL_H_
  #include "NETWORK.h"

  enum messagetypes  { HEARTBEAT = 0, SYNC=1, CHAT=2, ACTOR=3, OBJECT=4 };
  enum clientcommands{ UPING = 0, UCREATE = 1, ULOGIN = 2,UlOGOUT = 3, UCHAT = 4, UMOVE = 5};
  enum servercommands{ SPONG = 0, SCREATE = 1, SLOGIN = 2,SlOGOUT = 3, SCHAT = 4, SMOVE = 5};

  vector<string> tokenize(const string& str, const string& delim);
  /**
   * \brief Structure defining how a client function looks like<br>
   *
   * TODO Description and better function indexing<br>
   * bugs: none found<br>
   */
  typedef struct clientfunction_entry {
    clientcommands cmd;
    void (*address)(int);
  }clientfunction_entry;

  /**
   * \brief Structure defining how a server function looks like<br>
   *
   * TODO Description and better function indexing<br>
   * bugs: none found<br>
   */
  typedef struct serverfunction_entry {
    servercommands cmd;
    void (*address)(int);
  }serverfunction_entry;

  /**
   * \brief The protocol class<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
   class protocol{
     public:
       void processTextCommandToServer(string command, clientinfo* client);
       void processTextCommandFromServer(string command, application* e);
   };

   /**
    * \brief Holding the functions executed (by server) on receiving a inbound protocol command<br>
    *
    * TODO Description<br>
    * bugs: none found<br>
    */
  class receivedbyserver : public protocol{
    public:
      static void c_ping(int clientid);
      static void c_create(int clientid);
      static void c_login(int clientid);
      static void c_logout(int clientid);
      static void c_chat(int clientid);
      static void c_cmd(int clientid);
  };

  /**
   * \brief Holding the functions executed (by client) on receiving a inbound protocol command<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class receivedbyclient : public protocol{
    public:
      static void s_pong(int clientid);
      static void s_create(int clientid);
      static void s_login(int clientid);
      static void s_logout(int clientid);
      static void s_chat(int clientid);
      static void s_cmd(int clientid);
  };

#endif  
