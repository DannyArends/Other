#ifndef __SDLCOMMON_H__
#define __SDLCOMMON_H__
#include "includes.h"
#include "DataStructures.h"

SDL_Surface* init_SDLmain(const unsigned int width,const unsigned int height,const unsigned int bpp);
int makeargv(char *s,const char *delimiters, char ***argvp);
void freemakeargv(char **argv);
bool initializeserver(ServerInfo* server);
void add_client(TCPsocket client,ServerInfo* server);
void checknewclients(ServerInfo* server);
void checkactivity(ServerInfo* server);
void connect_to_local(ApplicationInfo* application);
void connect_to_server(const char* location, const int port, TCPsocket* client);
void server_down(ServerInfo* server);

#endif
