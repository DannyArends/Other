/**
 * \file GUI/widgets/inputbox.h
 * \brief Header file, for GUI/widgets/inputbox.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef INPUTBOX_H_
  #define INPUTBOX_H_
  #include "WIDGETS.h"
  
  /** 
      * \brief Two dimensional inputbox used for user-inputtext in hud
      */    
  class inputbox: public widget{
  public:
    inputbox(void);
    inputbox(hud* huddisplay);

    void addcharacter(char ch);
    string getinputtext(void);
    void sethidden(bool hidden);
    void backspace(void);
    void clear(void);
    ~inputbox(void);
    void render(void);
  private:
    string makepasswordstring(string inputstr);
    void init();
    bool hidden;
    text*  t;
    string inputtext;
};

#endif
