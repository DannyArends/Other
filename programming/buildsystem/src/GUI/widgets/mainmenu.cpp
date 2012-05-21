/**
 * \file GUI/widgets/mainmenu.cpp
 * \brief Code file, Implementation of class: \ref mainmenu
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "mainmenu.h"

mainmenu::mainmenu(hud* huddisplay) : widget::widget(huddisplay){
  this->type=MAINMENUWIDGET;
  this->color=GRAY20;
  init();
}

void mainmenu::init(){
  button* b = new button(huddisplay);
  b->settext("File");
  b->setlocation(10,10);
  this->addwidget(b);
  b = new button(huddisplay);
  b->settext("Edit");
  b->setlocation(110,10);
  this->addwidget(b);
  b = new button(huddisplay);
  b->settext("View");
  b->setlocation(210,10);
  this->addwidget(b);
  b = new button(huddisplay);
  b->settext("Info");
  b->setlocation(310,10);
  this->addwidget(b);
  resize();
}

void mainmenu::resize(void){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==SQUAREWIDGET){
      square* s = (square*)w;
      s->setsize(huddisplay->getwidth(),50);
      s->setcolor(this->color);
    }
  }
}

mainmenu::~mainmenu(void){

}

void mainmenu::render(void){
  glPushMatrix();
	for(int c=(this->getchildren().size()-1);c>=0;c--){
    widget* w = (widget*)this->getchildren()[c];
    w->render();
  }
  glPopMatrix();
}
