/**
 * \file GUI/widgets/button.cpp
 * \brief Code file, Implementation of class: \ref button
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "button.h"

/**
* Constructor of the button class.<br> 
* bugs: none found
*/
button::button(void) : widget::widget(){
  this->type=BUTTONWIDGET;
}

/**
* Constructor of the button class.<br> 
* bugs: none found
* @param huddisplay pointer to the HUD on which this button is drawn<br>
*/
button::button(hud* huddisplay) : widget::widget(huddisplay){
  this->type=BUTTONWIDGET;
  this->huddisplay->getscreenhandler()->monitorwidget(this);
  text* t = new text(huddisplay);
  t->setlocation(5,1);
  this->addwidget(t);
  init();
}

/**
* button initialization, pretty trivial, atm because we just test the settext function.<br> 
* bugs: none found
*/
void button::init(){
  this->settext("Button");  
}

/**
* Sets the displayed text of the button (and resizes if needed).<br> 
* bugs: none found
* @param line std::string holding the text to put on the button<br>
*/
void button::settext(string line){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==TEXTWIDGET){
      text* t = (text*)w;
      t->clear();
      t->addline(line);
      t->resize();
    }
    if(w->type==SQUAREWIDGET){
      square* s = (square*)w;
      s->setsize(5+(line.length()*16),18);
      this->setsize(5+(line.length()*16),18);
    }
  }
}

void button::runtask(void){
  string command = "login:";
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==INPUTBOXWIDGET){
      inputbox* ib = (inputbox*)w;
      command = command + ib->getinputtext() + ":";
    }
  }
  this->huddisplay->getcloudentry()->sendcommand(command);
}

/** 
* bugs: none found
*/
button::~button(void){

}

/**
* Called to render the button<br> 
* bugs: none found
*/
void button::render(void){
  glPushMatrix();
  //glColor3f(1.0,1.0,1.0);
  glTranslated(this->getx(),this->gety(),0);
	for(int c=(this->getchildren().size()-1);c>=0;c--){
    widget* w = (widget*)this->getchildren()[c];
    w->render();
  }
  glPopMatrix();
}
