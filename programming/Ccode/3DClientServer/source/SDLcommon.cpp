#include "SDLcommon.h"
#include "DataStructures.h"
#include "Error.h"

SDL_Surface* init_SDLmain(const unsigned int width,const unsigned int height,const unsigned int bpp){
  SDL_Surface *screen;
  char* progbar = new char[100];

  if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) exit_error("Unable to init SDL\n");
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  if ((screen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL)) == NULL) exit_error("Unable to set 640x480 video mode");
  sprintf(progbar,"Prog v0.1 using openGL %s ", (char *) glGetString(GL_VERSION));
  SDL_WM_SetCaption(progbar, "Prog v0.1" );
  SDL_EnableKeyRepeat(1,1);
  glEnable (GL_DEPTH_TEST);
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  
  return screen;
}

// splits a char* into a char ** based on the delimiters
int makeargv(char *s,const char *delimiters, char ***argvp){
	int i, numtokens;
	char *snew, *t;

	if ((s == NULL) || (delimiters == NULL) || (argvp == NULL))
		return -1;

	*argvp = NULL;
	snew = s + strspn(s, delimiters);
	if ((t = (char*)malloc(strlen(snew) + 1)) == NULL)
		return -1;
	strcpy(t, snew);	// It's fine that this isn't strncpy, since t is sizeof(snew) + 1.

	numtokens = 0;
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);

	if ((*argvp = (char**)malloc((numtokens + 1)*sizeof(char *))) == NULL){
		free(t);
		return -1;
	}
	if (numtokens == 0)
		free(t);
	else{
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}
	*((*argvp) + numtokens) = NULL;
	return numtokens;
}

//frees the char** created by makeargv
void freemakeargv(char **argv){
	if (argv == NULL)
		return;
	if (*argv != NULL)
		free(*argv);
	free(argv);
}



bool initializeserver(ServerInfo* server){
  if (SDLNet_Init() < 0) exit_error("Init SDL_Net");
  if (SDLNet_ResolveHost(&server->ip, NULL, 2000) < 0) exit_error("Resolving host");
  if (!(server->socket = SDLNet_TCP_Open(&server->ip))) exit_error("Opening port (already in use?)");
  server->num_clients=0;
  server->clients=SDLNet_AllocSocketSet(1000);
  if(!server->clients) exit_error("SDLNet_AllocSocketSet failed\n");
  printf("Server started port: %d\n", SDLNet_Read16(&server->ip.port));
  return true;
}

void add_client(TCPsocket client,ServerInfo* server){
  int num;
  num = SDLNet_TCP_AddSocket(server->clients,client);
  if(num==-1) {
    printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
  }
  server->num_clients++;
}

void checknewclients(ServerInfo* server){
  TCPsocket socket;
  IPaddress *ip;
  if ((socket = SDLNet_TCP_Accept(server->socket))){
    if ((ip = SDLNet_TCP_GetPeerAddress(socket))){
      printf("Client connected: %x %d\n", SDLNet_Read32(&(ip->host)), SDLNet_Read16(&(ip->port)));  
      add_client(socket,server);
    }else{
      fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
    }
  }
}

void checkactivity(ServerInfo* server){
  int numready;
  TCPsocket client;

  numready=SDLNet_CheckSockets(server->clients, 20);
  if(numready==-1) {
    SDL_Delay(20);
  }
  else if(numready) {
    printf("There are %d sockets with activity!\n",numready);
    // check all sockets with SDLNet_SocketReady and handle the active ones.
    if(SDLNet_SocketReady(server->socket)) {
      client=SDLNet_TCP_Accept(server->socket);
      if(client) {
      printf("Active client\n");
      }
    }
  }
}


void connect_to_local(ApplicationInfo* application){
  IPaddress ip;
  if(SDLNet_ResolveHost(&ip,"localhost",2000)==-1) {
      printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
  }
  application->client=SDLNet_TCP_Open(&ip);
  if(!application->client) {
    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
  }
   printf("Connection to localhost\n");
}

void connect_to_server(const char* location, const int port, TCPsocket* client){
  IPaddress ip;
  TCPsocket tcpsock;
  if(SDLNet_ResolveHost(&ip,location,port)==-1) {
      printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
  }
  tcpsock=SDLNet_TCP_Open(&ip);
  if(!tcpsock) {
    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
  }
  printf("Connection to remote host at %s:%d\n",location,port);
}

void server_down(ServerInfo* server){
    /* Close the client socket */
    SDLNet_FreeSocketSet(server->clients);
    server->num_clients--;
}
