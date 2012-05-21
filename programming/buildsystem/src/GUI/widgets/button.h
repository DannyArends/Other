/**
 * \file GUI/widgets/button.h
 * \brief Header file, for GUI/widgets/button.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef BUTTON_H_
  #define BUTTON_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Two dimensional button used in hud
      */  
  class button: public widget, public taskholder{
  public:
    button(void);
    button(hud* huddisplay);
    void settext(string line);
    virtual void runtask(void); // Default task: sending things to server
    ~button(void);
    void render(void);
  private:
    void init();
};

#endif
