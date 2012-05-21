/**
 * \file NETWORK/httpserver.cpp
 * \brief Code file, Implementation of class: \ref httpserver
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "httpserver.h"

void send_head(TCPsocket conn, int stat, int len);

void* starthttpserver(void* ptr){
  sdlserverstruct* application = (sdlserverstruct*)ptr;
  TCPsocket socket;
	TCPsocket	conn;
	int		        n;
	char		      buff[BUFFER1024], cmd[BUFFER16], path[BUFFER64], vers[BUFFER16];
	char*         timestr;
  time_t        tv;
  IPaddress*    ip = new IPaddress();
	if (SDLNet_Init() < 0){
	  cerr << "[HTTPSERVER]\terror sdl init: " << SDLNet_GetError() << endl;
    pthread_exit((void*) 0);
  }
	if (SDLNet_ResolveHost(ip, NULL, 80) < 0){
	  cerr << "[HTTPSERVER]\terror resolving: " << SDLNet_GetError() << endl;
    pthread_exit((void*) 0);
  }
	if (!(socket = SDLNet_TCP_Open(ip))){
	  cerr << "[HTTPSERVER]\terror opening: " << SDLNet_GetError() << endl;
    pthread_exit((void*) 0);
  }
	cout << "[HTTPSERVER]\tMonitoring for clients on port: 2000" << endl;
  while(application->running){
		/* wait for contact from a client on specified appnum */
    sleep(20);
		conn = SDLNet_TCP_Accept(socket);
		if (conn){
    /* read and parse the request line */
		n = SDLNet_TCP_Recv(conn, buff, BUFFER1024);
		sscanf(buff, "%s %s %s", cmd, path, vers);
    printf("[HTTPSERVER]\tCommand: %s for path: %s\n",cmd,path);
		/* check for a request that we cannot understand */
		if (strcmp(cmd, "GET") || (strcmp(vers, "HTTP/1.0") && strcmp(vers, "HTTP/1.1"))) {
			send_head(conn, 400, strlen(ERROR_400));
			(void) SDLNet_TCP_Send(conn, ERROR_400, strlen(ERROR_400));
			continue;
		}

		/* send the requested web page or a "not found" error */
		if (strcmp(path, "/") == 0) {
			send_head(conn, 200, strlen(HOME_PAGE));
			(void) SDLNet_TCP_Send(conn, HOME_PAGE, strlen(HOME_PAGE));
		} else if (strcmp(path, "/time") == 0) {
			time(&tv);
			timestr = ctime(&tv);
			(void) sprintf(buff, TIME_PAGE, timestr);
			send_head(conn, 200, strlen(buff));
			(void) SDLNet_TCP_Send(conn, buff, strlen(buff));
		} else { /* not found */
      (void) sprintf(buff, ERROR_404, path);
			send_head(conn, 404, strlen(ERROR_404));
			(void) SDLNet_TCP_Send(conn, buff, strlen(buff));
		}
    printf("[HTTPSERVER]\tDone handling request\n");
    }
	}
  SDLNet_TCP_Close(socket);
	//SDLNet_Quit();
  pthread_exit((void*) 0);
  return((void*) 0);
}

httpserver::httpserver(sdlserverstruct* application){
  cout << "[STARTUP]\tHTTPserver" << endl;
  this->sdlthread.rvalue = (int)pthread_create(&sdlthread.thread, NULL, starthttpserver, (void*) application);
}

httpserver::~httpserver(){
  SDLNet_Quit();
}

/**
* C-routine that sends a http header to a connecting machine<br>
* bugs: none found<br>
* @param conn Connection that is being served<br>
* @param stat HTTP statuscode to retrun<br>
* @param len Length of the returned message (without the HTTP header)<br>
*/
void send_head(TCPsocket conn, int stat, int len){
	char	*statstr, buff[BUFFER1024];
	/* convert the status code to a string */
	switch(stat) {
	case 200:
		statstr = (char*)"OK";
		break;
	case 400:
		statstr = (char*)"Bad Request";
		break;
	case 404:
		statstr = (char*)"Not Found";
		break;
	default:
		statstr = (char*)"Unknown";
		break;
	}
  
	(void) sprintf(buff, "HTTP/1.0 %d %s\r\n", stat, statstr);
  (void) SDLNet_TCP_Send(conn, buff, strlen(buff));

	(void) sprintf(buff, "Server: %s\r\n", SERVER_NAME);
  (void) SDLNet_TCP_Send(conn, buff, strlen(buff));

	(void) sprintf(buff, "Content-Length: %d\r\n", len);
  (void) SDLNet_TCP_Send(conn, buff, strlen(buff));

	(void) sprintf(buff, "Content-Type: text/html\r\n");
  (void) SDLNet_TCP_Send(conn, buff, strlen(buff));

	(void) sprintf(buff, "\r\n");
  (void) SDLNet_TCP_Send(conn, buff, strlen(buff));
}

