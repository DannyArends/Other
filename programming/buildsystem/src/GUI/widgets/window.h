/**
 * \file GUI/widgets/window.h
 * \brief Header file, for GUI/widgets/window.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef WINDOW_H_
  #define WINDOW_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Two dimensional window holding other widgets.
      */   
  class window: public widget{
  public:
    window(void);
    window(hud* huddisplay);
    ~window(void);
    void settitle(string title);
    void render(void);
  private:
    void init();
    string title;
};

#endif
