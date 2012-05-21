/**
 * \file GUI/widgets/widgetfactory.h
 * \brief Header file, for GUI/widgets/widgetfactory.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef WIDGETFACTORY_H_
  #define WIDGETFACTORY_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Factoryclass for creating and managing all widgets.
      */     
  class widgetfactory{
  public:
    widgetfactory(hud* huddisplay);
    window* createwindow(void);
    ~widgetfactory(void);
  private:
    hud* hudisplay;
};

#endif
