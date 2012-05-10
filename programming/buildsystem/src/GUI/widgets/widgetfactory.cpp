/**
 * \file GUI/widgets/widgetfactory.cpp
 * \brief Code file, Implementation of class: \ref widgetfactory
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "widgetfactory.h"

widgetfactory::widgetfactory(hud* huddisplay){
  this->hudisplay=huddisplay;
}

window* widgetfactory::createwindow(void){
  window* w = new window(this->hudisplay);
  return w;
}

widgetfactory::~widgetfactory(void){

}
