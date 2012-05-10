/**
 * \file GUI/widgets/text.cpp
 * \brief Code file, Implementation of class: \ref text
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "text.h"

text::text(void) : widget::widget(){
  this->type=TEXTWIDGET;
  this->setcolor(WHITE);
  init();
}

text::text(hud* huddisplay) : widget::widget(huddisplay){
  this->type=TEXTWIDGET;
  this->setcolor(WHITE);
  init();
}

void text::init(){
  this->scale=1.0;
  this->textset=0;
  this->c=false;
}

text::~text(void){
  this->data.clear();
}

void text::setscale(float scale){
  this->scale=scale;
}

void text::centered(bool c){
  this->c=c;
}

bool text::iscentered(void){
  return this->c;
}

uint  text::gettextlength(void){
  uint cmax = 0;
  for(uint x=0;x<data.size();x++){
    if(data[x].length() > cmax){
    cmax = data[x].length();
    }
  }
  return (uint)((15*cmax)*this->scale);
}

void text::setstyle(int style){
  this->textset=style;
}

void text::addline(string line){
  this->data.push_back(line);
}

uint  text::getlines(void){
  return this->data.size();
}

string  text::getline(uint key){
  if(this->data.size() <= key) return "no such line";
  return this->data[key];
}

void text::clear(void){
  this->data.clear();
}

void text::addline(const char *fmt, ...){
  char		text[1024];									// Holds Our String
	va_list ap;											// Pointer To List Of Arguments
	
  va_start(ap, fmt);										// Parses The String For Variables
	vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);												// Results Are Stored In Text
  this->data.push_back(string(text));
}

void text::render(void){
  glPushMatrix();
  glColor3f(this->getcolor().r,this->getcolor().g,this->getcolor().b);
  for(uint l=0;l<this->data.size();l++){
    char buffer[1024];
    sprintf(buffer, this->data[l].c_str());							// And Converts Symbols To Actual Numbers
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->huddisplay->getfonttextureid());
    glTranslated(this->getx()+(l*16)*this->scale,this->gety(),0);
  	glListBase(this->huddisplay->getbase()-32+(128*textset));
  	glScalef(this->scale,this->scale,this->scale);
  	glCallLists(strlen(buffer),GL_UNSIGNED_BYTE, buffer);
  	glDisable(GL_TEXTURE_2D);
  }
   glPopMatrix();
}

