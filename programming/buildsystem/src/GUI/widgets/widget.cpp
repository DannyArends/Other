/**
 * \file GUI/widgets/widget.cpp
 * \brief Code file, Implementation of class: \ref widget
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "WIDGETS.h"

widget::widget() : object2d::object2d(){
  this->name="none";
  this->color=WHITE;
  this->setsize(1,1);
  this->type=UNDEFWIDGET;  
}

widget::widget(hud* huddisplay) : object2d::object2d(){
  this->name="none";
  this->color=WHITE;
  this->huddisplay=huddisplay;
  square* s = new square();
  s->setsize(1,1);
  s->setcolor(GRAY70);
  this->addwidget(s);
  this->type=UNDEFWIDGET;
}

void widget::resize(void){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = this->getchildren()[c];
    if(w->type==SQUAREWIDGET){
      square* s = (square*)w;
      s->setsize(this->getsizex(),this->getsizey());
    }
    if(w->type==TEXTWIDGET){
      text* t = (text*)w;
      if(t->iscentered()){
        t->setlocation((this->getsizex()-(t->gettextlength()))/2,2);
      }
    }      
  }
}

uint widget::getscreenx(void){
  if(this->getparent()!=0) return (this->getx()+this->getparent()->getscreenx());
  return this->getx();
}
uint widget::getscreeny(void){
  if(this->getparent()!=0) return (this->gety()+this->getparent()->getscreeny());
  return this->gety();
}
