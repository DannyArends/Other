/**
 * \file GUI/engine.h
 * \brief Header file, for GUI/engine.cpp
 *
 * This class is the engine<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef ENGINE_H_
  #define ENGINE_H_
  #include "GUI.h"
  /**
   * \brief OpenGL rendering engine<br>
   *
   * bugs: none found<br>
   */
  class engine{
    public:
      engine(application* app);
      ~engine();
      /**
      * \brief Return a pointer to the application object<br>
      * bugs: none found<br>
      */
      application*    getapplication(void);
      /**
      * \brief Return a pointer to the screenhandler<br>
      * bugs: none found<br>
      */
      screenhandler*  getscreenhandler(void);
      /**
      * Return a pointer to the filesystem<br>
      * bugs: none found<br>
      */
      myio*           getfilesystem(void);
      /**
      * \brief Return a pointer to the threadhandler<br>
      * bugs: none found<br>
      */
      mythreader*     getthreadpool(void);
      /**
      * \brief Return a pointer to engine specific information<br>
      * bugs: none found<br>
      */
      engineinfo*     getinfo(void);
      /**
      * \brief Return a pointer to the gameworld<br>
      * bugs: none found<br>
      */
      universe*       getuniverse(void);
      /**
      * \brief Return a pointer to the 2D head up display (hud)<br>
      * bugs: none found<br>
      */
      hud*            gethud(void);
      bool            movecamera(int x, int y, int z);
      bool            rotatecamera(int x, int y, int z);
      /**
      * \brief Shutdown the engine<br>
      * bugs: none found<br>
      */
      void            shutdown(void);
      /**
      * \brief Don't forget to initialize the engine<br>
      * bugs: none found<br>
      */
      bool            init(void);
      void            draw(void);
      void            resize(SDL_Event event);
      hud*            hudisplay;
    protected:
      void            checknetworkevents(cloudmember* networkentry);
      void            loadinitconfig(application* app);
      application*    myapplication;
      mythreader*     threadpool;
      engineinfo*     info;
      universe*       worlddisplay;
      screenhandler*  evthandler;
    private:
      SDL_Surface*    screen;
      SDL_Event       event;
  };
  
#endif
