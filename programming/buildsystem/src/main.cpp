/**
 * \file main.cpp
 * \brief Code file, holding application entry point
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "main.h"
using namespace std;



application::application(){
  this->myconfigfile= new configfile("config.ini");
  this->filesystem= new myio();
  this->time = new timeserver();
  this->information=new sdlserverstruct();
  this->information->running = true;
  this->information->ourtime=this->time;
  this->db = new database();
  #ifdef USE_NETWORK
    sdl = new sdlserver(getsdlserverstruct(),this->myconfigfile);
    this->time->addchild(sdl);
    http = new httpserver(getsdlserverstruct());
  #endif

}

configfile* application::getconfigurationfile(void){
  return this->myconfigfile;
}

sdlserverstruct* application::getsdlserverstruct(void){
  return this->information;
}

database* application::getdatabase(void){
  return this->db;
}

myio* application::getfilesystem(void){
  return this->filesystem;
}

#ifdef USE_NETWORK
  sdlserver* application::getsdlserver(void){
    return this->sdl;
  }

  httpserver* application::gethttpserver(void){
    return this->http;
  }

  cloudmember* application::getcloudmember(void){
    return this->sdl->getcloud();
  }
#endif

#ifdef USE_GUI

  engine* application::getgui(void){
    return this->gui;
  }

  void application::setgui(engine* guiengine){
    this->gui=guiengine;
  }

#endif

#ifdef WINDOWS

int Main(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
  cout << "Startup of BUILDSYSTEM Version " << VERSION_MAJOR << "." << VERSION_MINOR << endl;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
    cerr << "[ENGINE]\tSDL initialization failed" << endl;
    return -1;
  }
  application* myapplication = new application();
  #ifdef USE_GUI
    new engine(myapplication);
  #endif
  return 0;
}

#ifdef WINDOWS

static int makeargv(char *s, char *delimiters, char ***argvp){
	int i, numtokens;
	char *snew, *t;

	if ((s == NULL) || (delimiters == NULL) || (argvp == NULL))	return -1;

	*argvp = NULL;
	snew = s + strspn(s, delimiters);
	if ((t = (char*)malloc(strlen(snew) + 1)) == NULL)	return -1;
	strcpy(t, snew);
	numtokens = 0;
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);

	if ((*argvp = (char**)malloc((numtokens + 1)*sizeof(char *))) == NULL){
		free(t);
		return -1;
	}
	if (numtokens == 0){
		free(t);
	}else{
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}
	*((*argvp) + numtokens) = NULL;
	return numtokens;
}

static void freemakeargv(char **argv){
	if (argv == NULL) return;
	if (*argv != NULL) free(*argv);
	free(argv);
}

int APIENTRY WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow){
	char **argv= NULL;
	int argc;
  char *win_command_line;
	win_command_line = (char*)GetCommandLine();
	argc = makeargv(win_command_line, (char*)" \t\n", &argv);
	Main(argc, (char **) argv);
	freemakeargv(argv);

	return 0;
}

#endif
