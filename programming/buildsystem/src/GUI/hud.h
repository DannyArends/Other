/**
 * \file GUI/hud.h
 * \brief Header file, for GUI/hud.cpp
 *
 * This class is used to separate two dimensional from three dimensional rendering within the engine<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef HUD_H_
  #define HUD_H_
  #include "GUI.h"
  /** 
  * \brief Head-up display for rendering twodimensional widgets.
  *
  * TODO Documentation<br>
  * Bugs: none found.<br>
  */
  class hud : public object2d, public renderable<object>, public node<widget>{
  public:
    hud(engine* e,tgaInfo* fonttexture);
    ~hud(void);

    void           setFPS(int fps);
    void           render(void);
    void           addLine(std::string line);
    screenhandler* getscreenhandler(void);
    cloudmember*   getcloudentry(void);
    GLvoid         glprint(GLint x, GLint y, int set, const char *fmt, ...);
    GLuint         getbase(void);
    void           resize(void);
    int            getwidth(void);
    int            getheight(void);
    GLuint         getfonttextureid(void);
  
  private:
    void           printinputline(void);
    void           initfont(void);
    void           deletefont(void);
    
    tgaInfo*       font;
    GLuint         textureid;
    GLuint	       base;
    engine*        myengine;
    
};
#endif
