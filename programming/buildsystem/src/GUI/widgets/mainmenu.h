/**
 * \file GUI/widgets/mainmenu.h
 * \brief Header file, for GUI/widgets/mainmenu.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef MAINMENU_H_
  #define MAINMENU_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Two dimensional mainmenu holding buttons.
      */    
  class mainmenu: public widget{
  public:
    mainmenu(hud* huddisplay);
    ~mainmenu(void);
    void resize(void);
    void render(void);
  private:
    void init();
};

#endif
