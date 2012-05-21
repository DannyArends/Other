/**
 * \file GUI/widgets/inputbox.cpp
 * \brief Code file, Implementation of class: \ref inputbox
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "inputbox.h"

inputbox::inputbox(void) : widget::widget(){
  this->type=INPUTBOXWIDGET;
}

inputbox::inputbox(hud* huddisplay) : widget::widget(huddisplay){
  this->huddisplay->getscreenhandler()->monitorwidget(this);
  this->init();
}

void inputbox::init(){
  this->type=INPUTBOXWIDGET;
  this->hidden=false;
  this->inputtext="";
  t = new text(this->huddisplay);
  t->addline(this->inputtext+"Click");
  t->setlocation(5,1);
  this->addwidget(t); 
  this->setsize(100,20);
  resize();
}

void inputbox::addcharacter(char ch){
  this->inputtext+=ch;
  t->clear();
  if(!hidden)t->addline(this->inputtext);
  if(hidden)t->addline(makepasswordstring(this->inputtext));
  this->setsize(5+(this->inputtext.length()*15),20);
  resize();
}

string inputbox::getinputtext(void){
  return this->inputtext;
}

void inputbox::sethidden(bool hidden){
  this->hidden=hidden;
}

void inputbox::backspace(void){
  if(this->inputtext.length()>0) this->inputtext.erase(this->inputtext.length()-1); 
  t->clear();
  if(!hidden)t->addline(this->inputtext);
  if(hidden)t->addline(makepasswordstring(this->inputtext));
  this->setsize(5+(this->inputtext.length()*15),20);
  resize();
}

string inputbox::makepasswordstring(string inputstr){
  string pass;
  for(uint c=0;c < inputstr.size();c++){
    pass += "#";
  }
  return pass;
}

void inputbox::clear(void){
  this->inputtext = "";
  t->clear();
  if(!hidden)t->addline(this->inputtext+"Click");
  if(hidden)t->addline(this->inputtext+"Click");
  this->setsize(5+(5*15),20);
  this->resize();
}

inputbox::~inputbox(void){

}

void inputbox::render(void){
  glPushMatrix();
  glColor3f(color.r,color.g,color.b);
  glTranslated(this->getx(),this->gety(),0);
	for(int c=(this->getchildren().size()-1);c>=0;c--){
    widget* w = (widget*)this->getchildren()[c];
    w->render();
  }
  glPopMatrix();
}
