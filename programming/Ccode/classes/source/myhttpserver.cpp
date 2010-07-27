#include "myhttpserver.h"


void* serverstart(void* ptr){
  server* myserver = (server*)ptr;
  printf("Starting http-server on thread %d\n", pthread_self());
  if (SDLNet_Init() < 0) printf("Init SDL_Net");
  if (SDLNet_ResolveHost(&myserver->ip, NULL, 80) < 0) printf("Resolving host");
  if (!(myserver->socket = SDLNet_TCP_Open(&myserver->ip))) printf("Opening port (already in use?)");
  myserver->numsessions=0;
  myserver->clients=SDLNet_AllocSocketSet(1000);
  if(!myserver->clients) printf("SDLNet_AllocSocketSet failed\n");
  printf("myserver started port: %d\n", SDLNet_Read16(&myserver->ip.port));
  while(myserver->running){
    TCPsocket socket;
    IPaddress *ip;
    if ((socket = SDLNet_TCP_Accept(myserver->socket))){
      if ((ip = SDLNet_TCP_GetPeerAddress(socket))){
        printf("Client connected: %x %d\n", SDLNet_Read32(&(ip->host)), SDLNet_Read16(&(ip->port)));
      }else{
        printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
      }
    }
  }
  pthread_exit((void*) 0);
}

void servershutdown(void* ptr){
  server* myserver = (server*)ptr;
  myserver->running=false;
}



/*-----------------------------------------------------------------------
 * send_head - send an HTTP 1.0 header with given status and content-len
 *-----------------------------------------------------------------------
 */
void
send_head(connection conn, int stat, int len){
	char	*statstr, buff[BUFFSIZE];

	/* convert the status code to a string */

	switch(stat) {
	case 200:
		statstr = "OK";
		break;
	case 400:
		statstr = "Bad Request";
		break;
	case 404:
		statstr = "Not Found";
		break;
	default:
		statstr = "Unknown";
		break;
	}
	
	/*
	 * send an HTTP/1.0 response with Server, Content-Length,
	 * and Content-Type headers.
	 */

	(void) sprintf(buff, "HTTP/1.0 %d %s\r\n", stat, statstr);
	(void) send(conn, buff, strlen(buff), 0);

	(void) sprintf(buff, "Server: %s\r\n", SERVER_NAME);
	(void) send(conn, buff, strlen(buff), 0);

	(void) sprintf(buff, "Content-Length: %d\r\n", len);
	(void) send(conn, buff, strlen(buff), 0);

	(void) sprintf(buff, "Content-Type: text/html\r\n");
	(void) send(conn, buff, strlen(buff), 0);

	(void) sprintf(buff, "\r\n");
	(void) send(conn, buff, strlen(buff), 0);
}


