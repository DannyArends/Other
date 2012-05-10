/**
 * \file GUI/engine.cpp
 * \brief Code file, Implementation of class: \ref engine
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "engine.h"


engine::engine(application* app){
  message("[ENGINE]\tStarting up");
  app->setgui(this);
  this->myapplication=app;
  loadinitconfig(app);
  this->threadpool= new mythreader();
  message("[ENGINE]\tThreadpool up");
  SDL_EnableUNICODE(1);
  SDL_WM_SetCaption("SDL OpenGL viewer", "Danny Arends");

  this->evthandler = new screenhandler(this);

  if (this->init()){
    while (this->myapplication->getsdlserverstruct()->running){
      //clock_t s = clock();
      draw();
      //clock_t e = clock();
      //cout << "DRAW took " << timedifference(s, e) << " msecs" << endl;
      checknetworkevents(this->myapplication->getcloudmember());
      if (SDL_PollEvent(&event)) {
        evthandler->handlesdlevent(event);
      }
      //clock_t e2 = clock();
      //cout << "Polling Events took "<< timedifference(e, e2) <<" msecs" << endl;
      SDL_Delay(40); 
    }
  }
}

application* engine::getapplication(void){
  return this->myapplication;
}

void engine::checknetworkevents(cloudmember* networkentry){
  for(uint x=0; x < networkentry->getchildren().size() ; x++){
    if(networkentry->getchildren()[x]->getinflag()){
      evthandler->handlenetworkevent(networkentry->getchildren()[x]->getlinebuffer());
      networkentry->getchildren()[x]->setinflag(false);
    }
  }
}

void engine::loadinitconfig(application* app){
  this->info = new engineinfo();
  this->info->width = app->getconfigurationfile()->read<int>("screenw",800);
  this->info->height= app->getconfigurationfile()->read<int>("screenh",600);
  this->info->bpp   = app->getconfigurationfile()->read<int>("screenbpp",0);
  this->info->texturedir  = app->getconfigurationfile()->read<string>("texturedir", "./textures");
  this->info->objectdir   = app->getconfigurationfile()->read<string>("objectdir", "./3ds");
  this->info->mapdir      = app->getconfigurationfile()->read<string>("mapdir", "./maps");
}

screenhandler* engine::getscreenhandler(void){
  return this->evthandler;
}

/**
* Return a pointer to the threadpool<br>
* bugs: none found<br>
*/
mythreader*    engine::getthreadpool(void){
  return this->threadpool;
}

/**
* Return a pointer to the filesystem<br>
* bugs: none found<br>
*/
myio*    engine::getfilesystem(void){
  return this->myapplication->getfilesystem();
}

/**
* Return a pointer to the 3D universe, containing all the renderables<br>
* bugs: none found<br>
*/
universe*      engine::getuniverse(void){
 return this->worlddisplay;
}

/**
* Return a pointer to the 2D universe, containing all the widgets<br>
* bugs: none found<br>
*/
hud*           engine::gethud(void){
 return this->hudisplay;
}

engineinfo*    engine::getinfo(void){
  return this->info;
}

/**
* Initialize the engine<br>
* bugs: none found<br>
*/
bool engine::init(void){
  if (!(screen = SDL_SetVideoMode(this->info->width, this->info->height, this->info->bpp, SDL_OPENGL|SDL_RESIZABLE))){
    SDL_Quit();
    cout << "[ENGINE]\tVideomode could not be set" << endl;
    return false;
  }else{
    cout << "[ENGINE]\tRenderer = " << glGetString(GL_RENDERER) << endl;
    cout << "[ENGINE]\tOpenGL version = " << glGetString(GL_VERSION) << endl;
    cout << "[ENGINE]\tVendor = " << glGetString(GL_VENDOR) << endl;
    //cout << "GL_EXTENSIONS = " << glGetString(GL_EXTENSIONS) << endl;

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    
    //Start out HUD and World
    string fontlocation = this->info->texturedir + "/font.tga";
    this->hudisplay = new hud(this,tgaLoad((char*)fontlocation.c_str()));
    this->worlddisplay = new universe(this);


    this->myapplication->getsdlserverstruct()->running = true;
    return true;
  }
}

/**
* Shutdown the engine<br>
* bugs: none found<br>
*/
void engine::shutdown(void){
  this->myapplication->getsdlserverstruct()->running=false;
}

/**
* Resize the window<br>
* bugs: none found<br>
* @param event SDL event holding the new width and height<br>
*/
void engine::resize(SDL_Event event){
  cout << "[ENGINE]\tWindow resized" << endl;
  screen = SDL_SetVideoMode(event.resize.w, event.resize.h, this->info->bpp, SDL_OPENGL|SDL_RESIZABLE);
  if(!screen){
    cout << "[ENGINE]\tNo screen after resize" << endl;
    exit(-1);
  }
  this->info->width=event.resize.w;
  this->info->height=event.resize.h;
  this->hudisplay->resize();
}

/**
* Move the camera<br>
* bugs: none found<br>
* @param x new x location of the camera<br>
* @param y new y location of the camera<br>
* @param z new z location of the camera<br>
*/
bool engine::movecamera(int x, int y, int z){
  worlddisplay->movecamera(x,y,z);
  return true;
}

/**
* Rotate the camera<br>
* bugs: none found<br>
* @param x new x rotation of the camera<br>
* @param y new y rotation of the camera<br>
* @param z new z rotation of the camera<br>
*/
bool engine::rotatecamera(int x, int y, int z){
  worlddisplay->rotatecamera(x,y,z);
  return true;
}

/**
* Draws the scene on the window<br>
* bugs: none found<br>
*/
void engine::draw(void){
  this->worlddisplay->render();
	this->hudisplay->render();
  SDL_GL_SwapBuffers();
}

/**
* bugs: none found<br>
*/
engine::~engine(){
  cout << "[ENGINE]\tStopping SDL" << endl;
  SDL_Quit();
}
