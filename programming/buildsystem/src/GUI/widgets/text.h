/**
 * \file GUI/widgets/text.h
 * \brief Header file, for GUI/widgets/text.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef TEXT_H_
  #define TEXT_H_
  #include "WIDGETS.h"
  
  /** 
  * \brief Widget holding 2D text.
  *
  * options:<br>
  * - Single line/Multi line<br>
  * - Centering<br>
  *
  * bugs: None found<br>
  */
  class text: public widget{
  public:
    text(void);
    text(hud* huddisplay);
    ~text(void);
    void setscale(float scale);
    void centered(bool c);
    bool iscentered(void);
    uint  gettextlength(void);
    uint  getlines(void);
    string  getline(uint key);
    void setstyle(int style);
    void clear(void);
    void addline(string line);
    void addline(const char *fmt, ...);
    void render(void);
  private:
    void init();  
    float          scale;
    bool           c;
    uint           textlength;
    int            textset;
    vector<string> data;
};

#endif
