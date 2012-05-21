/**
 * \file GUI/screenhandler.h
 * \brief Header file, for GUI/screenhandler.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef SCREENHANDLER_H_
  #define SCREENHANDLER_H_
  #include "GUI.h"

/**
* \brief Opengl window event handler<br>
*
* bugs: none found<br>
*/
class screenhandler{
	public:
  screenhandler(engine* e);
  const char* getinputstring(void);
  void monitorwidget(widget* w);
  bool checkwidgets(uint x,uint y);
  ~screenhandler();
	void handlesdlevent(SDL_Event event);
	void handlenetworkevent(string event);
	void getworldcoordinate(int x, int y);
  private:
  engine*           myengine;
  vector<widget*>   monitoredwidgets;
  int               activeinput;
  string            input;
};

void GetOGLPos(int x, int y);
#endif
