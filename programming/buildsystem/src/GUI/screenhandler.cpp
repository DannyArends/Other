/**
 * \file GUI/screenhandler.cpp
 * \brief Code file, Implementation of class: \ref screenhandler
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "screenhandler.h"

/**
* screenhandler class.<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
screenhandler::screenhandler(engine* e){
  this->myengine=e;
  this->input="";
  this->activeinput=-1;
}

screenhandler::~screenhandler(){

}

/*
 * \brief Returns the main input string
 *
*/
const char* screenhandler::getinputstring(void){
  return this->input.c_str();
}

/*
 * \brief Handles network event that target the GUI
 *
 * Should only receive a subset of all network events,
 * no need to let the GUI do the work that should be done by SDL
 * The screenhandler should just split things in 2, a part for 3D (entityfactory)and
 * a part for 2D (widgetfactory)
*/
void screenhandler::handlenetworkevent(string event){
  receivedbyclient* e = new receivedbyclient();
  e->processTextCommandFromServer(event,this->myengine->getapplication());
}

/*
 * \brief handles SDL events coming from the GUI and keyboard
 *
 * Should only handle a very small subset of features directly
 * Better create a server command for it
*/
void screenhandler::handlesdlevent(SDL_Event event){
  switch (event.type) {
  /* handle the keyboard */
    case SDL_QUIT:
      myengine->shutdown();
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          myengine->shutdown();
          break;
        case SDLK_UP:
          myengine->movecamera(0,0,2);
          break;
        case SDLK_DOWN:
          myengine->movecamera(0,0,-2);
          break;
        case SDLK_PAGEUP:
          myengine->movecamera(0,2,0);
          break;
        case SDLK_PAGEDOWN:
          myengine->movecamera(0,-2,0);
          break;           
        case SDLK_LEFT:
          myengine->movecamera(2,0,0);
          break; 
        case SDLK_RIGHT:
          myengine->movecamera(-2,0,0);
          break; 
        case SDLK_PERIOD:
          myengine->rotatecamera(0,10,0);
          break; 
        case SDLK_COMMA:
          myengine->rotatecamera(0,-10,0);
          break; 
        case SDLK_SPACE:
          if(this->activeinput<0){
            this->input += " ";
          }else{
            inputbox* ib = (inputbox*)this->monitoredwidgets[this->activeinput];
            ib->addcharacter(' ');
          }
          break;
        case SDLK_RETURN:
          if(this->activeinput<0){
            //Send it to the cloud we don't need it anymore
            this->myengine->getapplication()->getcloudmember()->sendcommand(this->input);
            //Clear the input
            this->input = "";
          }else{
            //Get a handle to the active input
            inputbox* ib = (inputbox*)this->monitoredwidgets[this->activeinput];
            //Send it to the cloud
            this->myengine->getapplication()->getcloudmember()->sendcommand(ib->getinputtext());
            //Clear the input
            ib->clear();
          }
          break;
        case SDLK_BACKSPACE:
          if(this->activeinput<0){
            if(this->input.length()>0) this->input.erase(this->input.length()-1); 
          }else{
            inputbox* ib = (inputbox*)this->monitoredwidgets[this->activeinput];
            ib->backspace();
          }
          break;
        default:
          char ch;
          if ( (event.key.keysym.unicode & 0xFF80) == 0 ) {
            ch = event.key.keysym.unicode & 0x7F;
          }
          if(this->activeinput<0){
            this->input += ch;
          }else{
            inputbox* ib = (inputbox*)this->monitoredwidgets[this->activeinput];
            ib->addcharacter(ch);
          }
          break;
      }
      break;
      case SDL_MOUSEMOTION:
        //message("Mouse moved by %d,%d to (%d,%d)", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
      break;
      case SDL_MOUSEBUTTONDOWN:
        message("[EVTHANDLER]\tMouse button %d pressed at (%d,%d)", event.button.button, event.button.x, event.button.y);
        if(!checkwidgets(event.button.x, event.button.y)){
        
         // window* w = new window(this->myengine->hudisplay);
         // w->setlocation(event.button.x, event.button.y);
         // this->myengine->hudisplay->addwidget(w);  
          //mythreader* t = this->myengine->getthreadpool();
          //t->addload(this->myengine->getuniverse()->pemitter);
          //t->start();
          getworldcoordinate(event.button.x, event.button.y);
        }
      break;  
      case SDL_VIDEORESIZE:
        myengine->resize(event);
      break;            
  }
}

/*
 * \brief Add a 2D widget to monitor
 *
 */
void screenhandler::monitorwidget(widget* w){
  cout << "[HANDLER]\tMonitoring new button at: " << w->getscreenx() << "," << w->getscreeny() << endl;
  this->monitoredwidgets.push_back(w);
}

/*
 * \brief Checks if a monitored widget is used
 *
 */
bool screenhandler::checkwidgets(uint x, uint y){
  for(uint w=0;w<this->monitoredwidgets.size();w++){
    //printf("[HANDLER]\tChecking: %d %d\n",this->monitoredwidgets[w]->getx(),this->monitoredwidgets[w]->gety());
    if(this->monitoredwidgets[w]->getscreenx() < x && this->monitoredwidgets[w]->getscreenx() + this->monitoredwidgets[w]->getsizex() > x){
      if(this->monitoredwidgets[w]->getscreeny() < y && this->monitoredwidgets[w]->getscreeny() + this->monitoredwidgets[w]->getsizey() > y){
        cout << "[HANDLER]\tTYPE: " << this->monitoredwidgets[w]->type << endl;
        switch (this->monitoredwidgets[w]->type){
          case WINDOWWIDGET: 
          break; 
          case BUTTONWIDGET:
            this->myengine->getthreadpool()->addload((button*)this->monitoredwidgets[w]);
            this->myengine->getthreadpool()->start();
          break;
          case INPUTBOXWIDGET:
            this->activeinput=w;
          break;
          case TIMEWIDGET:
            this->myengine->getthreadpool()->addload((timeclock*)this->monitoredwidgets[w]);
            this->myengine->getthreadpool()->start();
          break;
          default:
          break;
        }
        return true;
      }
    }
  }
  this->activeinput=-1;
  return false;
}

/*
 * \brief Used for translating coordinates from 2D screen into 3D world
 *
 */
void screenhandler::getworldcoordinate(int x, int y){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	//printf("win: x: %f,y: %f,z: %f\n",winX, winY, winZ);
	//cout << "[WORLD]\tWorld position (" << posX << "," << posY << "," << posZ << ")" <<endl;
}
