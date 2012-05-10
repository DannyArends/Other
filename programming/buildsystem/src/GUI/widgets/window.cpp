/**
 * \file GUI/widgets/window.cpp
 * \brief Code file, Implementation of class: \ref window
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "window.h"

window::window(void) : widget::widget(){
  this->color=GRAY20;
  this->type=WINDOWWIDGET;
  this->setsize(200,150);
}

window::window(hud* huddisplay) : widget::widget(huddisplay){
  this->color=GRAY20;
  this->type=WINDOWWIDGET;
  this->setsize(200,150);
  text* t = new text(huddisplay);
  t->addline(string("window"));
  t->centered(true);
  this->addwidget(t);
  init();
}

void window::init(){
  
  button* b = new button(huddisplay);
  b->setparent(this);
  b->setlocation(5,20);

  //Attach 2 inputboxes to the button
  inputbox* ib = new inputbox(huddisplay);
  ib->setparent(this);
  ib->setlocation(5,40);
  b->addwidget(ib);
  inputbox* ib2 = new inputbox(huddisplay);
  ib2->setparent(this);
  ib2->setlocation(5,60);
  ib2->sethidden(true);
  b->addwidget(ib2);
  this->addwidget(b);

  resize();
}

window::~window(void){

}

void window::settitle(string title){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = (widget*)this->getchildren()[c];
    if(w->type==TEXTWIDGET){
    text* t = (text*)w;
    t->clear();
    t->addline(title);
    } 
  }
}

void window::render(void){
  glPushMatrix();
  glColor3f(color.r,color.g,color.b);
  glTranslated(this->getx(),this->gety(),0);
	for(int c=(this->getchildren().size()-1);c>=0;c--){
    widget* w = (widget*)this->getchildren()[c];
    w->render();
  }
  glPopMatrix();
}
