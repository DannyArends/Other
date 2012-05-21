/**
 * \file GUI/widgets/WIDGETS.h
 * \brief Header file, for the GUI/WIDGETS directory
 *
 * This class is used to share the objects within the GUI/WIDGETS directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * - \ref text<br>
 * - \ref window<br>
 * - \ref mainmenu<br>
 * - \ref button<br> 
 * - \ref inputbox<br> 
 * - \ref square<br> 
 * - \ref widgetfactory<br>  
 * 
 **/
 
#ifndef WIDGETS_H_
  #define WIDGETS_H_
  #include "GUI/GUI.h"
  
  enum WidgetType { UNDEFWIDGET = -1, WINDOWWIDGET = 0, MAINMENUWIDGET = 1, BUTTONWIDGET = 2, INPUTBOXWIDGET = 3, TEXTWIDGET=4, SQUAREWIDGET=5, TIMEWIDGET=6};
  
  /** 
  * \brief The superclass of all the two dimensional widgets.
  */
  class widget:public object2d, public renderable<object>, public node<widget>{
    public:
      widget();
      widget(hud* huddisplay);
      virtual ~widget(void){ };
      void        setcolor(RGBcolor color){ this->color=color; }
      RGBcolor    getcolor(void){ return this->color; }
      uint        getscreenx(void);
      uint        getscreeny(void);
      void        resize(void);
      void        addwidget(widget* child){this->addchild(child);}
      WidgetType  type;
    protected:
      virtual void init()=0;
      string      name;
      hud*        huddisplay;
      RGBcolor    color;
  };
  
  class text;
  class window;
  class mainmenu;
  class button;
  class inputbox;
  class square;
  class timeclock;
  class widgetfactory;
  
  #include "mainmenu.h"
  #include "window.h"
  #include "text.h"
  #include "widgetfactory.h"
  #include "button.h"
  #include "inputbox.h"
  #include "square.h"
  #include "timeclock.h"
#endif
