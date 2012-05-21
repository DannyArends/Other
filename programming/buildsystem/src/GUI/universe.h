/**
 * \file GUI/universe.h
 * \brief Header file, for GUI/universe.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef UNIVERSE_H_
  #define UNIVERSE_H_
  #include "GUI.h"

  /** 
  * \brief Class holding objects in the universe
  *
  * TODO Description<br>
  * bugs: none found
  */
  class universe : public renderable<object>, public node<entity>{
  public:
    universe(engine* e);
    ~universe(void);
    bool          movecamera(int x, int y, int z);
    bool          rotatecamera(int x, int y, int z);
    bool          setupviewport(void);
    engine*       getengine(void);
    void          render(void);
    emitter*      pemitter;
  private:
    void          setupcamera(void);
    void          loadterrain(void);
    void          loadobjects(void);
    engine*             myengine;
    entityfactory*      myentities;
    terrain*            map;
    int                 framecount;
    camera*             mycam;
};
#endif
