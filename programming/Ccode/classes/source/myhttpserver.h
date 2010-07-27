#include "includes.h"
#ifndef __MYHTTPSERVER_H__
#define __MYHTTPSERVER_H__

struct session {
  bool active;
  pthread_t clientthread;
};

struct server {
  bool      running;
  pthread_t serverthread;
  TCPsocket socket;
  IPaddress ip;
  int       numsessions;
  session*  sessions;
  SDLNet_SocketSet clients;
};

void* serverstart(void* ptr);
void servershutdown(void* ptr);
void* clientsession(void* ptr);
void sessionshutdown(void* ptr);
void servehttp(void* ptr);



#endif
