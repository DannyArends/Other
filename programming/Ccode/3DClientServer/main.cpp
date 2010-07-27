#include "includes.h"
#include "DataStructures.h"
#include "Error.h"
#include "OpenGL.h"
#include "2dWindow.h"
#include "SDLcommon.h"
#include "FileIO.h"
#include "MAPLoader.h"
#include "TGALoader.h"
#include "3dsSupport.h"
#include "Handlers.h"

#undef NO_STDIO_REDIRECT 

static GLint T0 = 0;  //Timepoint 0
static GLint K0 = 0;  //Time since last keyboard
static GLint M0 = 0;  //time since last mouse
static GLint Frames = 0;
static ApplicationInfo MyApp;

static struct option long_options[] = {
  {0, 0, 0, 0}
};

int APIENTRY WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow){
	char **argv= NULL;
	int argc;
  char   *win_command_line;
	win_command_line = GetCommandLine();
	argc = makeargv(win_command_line,(const char*)" \t\n", &argv);
	main(argc, (char **) argv);
	freemakeargv(argv);  
}

int main(int argc,char *argv[]) {
  bool verbose       = false;
  bool help          = false;
  char c;
  GLint t;
  int option_index   = 0;
  FILE *stream; 
  stream = freopen("CON", "w", stdout); 
  printf("\nProgram v0.0\n");
  while ((c = getopt_long(argc, argv, "vh",long_options, &option_index)) != -1){
    switch (c) {
    case 'v':
      verbose = true;
      break;
    case 'h':
      help = true;
      break;
    default:
      //printf("unknown option '%c'.\n", optopt);
      break;
    }
  }
  if(help){
    exit_help("\n");
  }else{
    //Main program
    SDL_Surface* screen;
    SDL_Event event;
    unsigned int width=1000;
    unsigned int height=500;
    unsigned int bpp=32;
    
    initializeserver(&(MyApp.server));
    connect_to_local(&(MyApp));
    checknewclients((&MyApp.server));
    screen = init_SDLmain(width,height,bpp);
    loadTextures(&MyApp);
    loadModels(&MyApp);
    loadMaps(&MyApp);
    setup_hud_new(&(MyApp.hud));
    setup_camera(&(MyApp.camera));
    while (true) {
      SDL_PollEvent(&event);
      switch (event.type) {
      case SDL_VIDEORESIZE:
        width = event.resize.w;
        height = event.resize.h;
        screen = init_SDLmain(width,height,bpp);
        break;
      case SDL_MOUSEBUTTONDOWN:
        t = SDL_GetTicks();
        //printf("Mouse button %d pressed at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
        if (t - M0 >= 200) {              //handle a key every 150 ms
          check_for_button(event.button.x, event.button.y, &MyApp.hud);
          M0=t;
        }
        break;
      case SDL_KEYDOWN:
          t = SDL_GetTicks();
          Uint8* keystate;
          keystate = SDL_GetKeyState(NULL);
          if(check_movement(&MyApp,keystate)){
            break;
          }
          if (t - K0 >= 150) {              //handle a key every 150 ms
            check_keydown(&MyApp,event,keystate);
            K0=t;
          }
        break;
      case SDL_QUIT:
        server_down(&MyApp.server);
        SDLNet_Quit();
        SDL_Quit();
        clearDisplayList(MyApp);
        cleanBuffers(&MyApp);
        exit(0);
      default:
        break;
      }
      checknewclients((&MyApp.server));
      checkactivity((&MyApp.server));
      render_scene(MyApp,width,height);
      Frames++;
      t = SDL_GetTicks();
      if (t - T0 >= 1000) {
        GLfloat seconds = (t - T0) / 1000.0;
        GLfloat fps = Frames / seconds;
        MyApp.fps = (int)fps;
        T0 = t;
        Frames = 0;
      }
    }
   }
  exit(0);
}
