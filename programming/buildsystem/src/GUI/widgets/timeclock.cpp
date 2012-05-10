/**
 * \file GUI/widgets/timeclock.cpp
 * \brief Code file, Implementation of class: \ref timeclock
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "timeclock.h"

timeclock::timeclock() :widget::widget(){
  this->type=TIMEWIDGET;
}

timeclock::timeclock(hud* hudisplay) :widget::widget(){
  this->type=TIMEWIDGET;
  this->huddisplay->getscreenhandler()->monitorwidget(this);
  text* t = new text(huddisplay);
  t->setlocation(5,1);
  this->addwidget(t);
  init();
}

/**
* Sets the displayed time of the timeclock (and resizes if needed).<br>
* bugs: none found
* @param line std::string holding the text to put on the button<br>
*/
void timeclock::settime(string line){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==TEXTWIDGET){
      text* t = (text*)w;
      t->clear();
      t->addline(line);
    }
    if(w->type==SQUAREWIDGET){
      square* s = (square*)w;
      s->setsize(5+(line.length()*16),18);
      this->setsize(5+(line.length()*16),18);
    }
  }
}

/**
* \brief Task from taskholder, (Threaded active polling of servertime)<br>
*
* bugs: none found
*/
void timeclock::runtask(void){
  string command = "ping:";
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==TEXTWIDGET){
      text* t = (text*)w;
      command = command + t->getline(0);
    }
  }
  this->huddisplay->getcloudentry()->sendcommand(command);
}

/**
* bugs: none found
*/
timeclock::~timeclock(void){

}

/**
* \brief Called to render the time widget<br>
*
* bugs: none found
*/
void timeclock::render(void){
  glPushMatrix();
  //glColor3f(1.0,1.0,1.0);
  glTranslated(this->getx(),this->gety(),0);
  for(int c=(this->getchildren().size()-1);c>=0;c--){
    widget* w = (widget*)this->getchildren()[c];
    w->render();
  }
  glPopMatrix();
}

/**
* \brief Called to initialize the clock
*
* Polls all the active servers for time, or display its internal timeclock
*
* bugs: none found
*/
void timeclock::init(void){

}
