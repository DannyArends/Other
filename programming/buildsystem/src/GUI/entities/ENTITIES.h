/**
 * \file GUI/entities/ENTITIES.h
 * \brief Header file, for the GUI/ENTITIES directory
 *
 * This class is used to share the objects within the GUI/ENTITIES directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * - \ref bone<br>
 * - \ref sphere<br>
 * - \ref line<br>
 * - \ref turtle<br> 
 * - \ref particle<br> 
 * - \ref terrain<br> 
 * - \ref skeleton<br> 
 * 
 **/
 
#ifndef ENTITIES_H_
  #define ENTITIES_H_
  #include "GUI/GUI.h"

  /** 
  * \brief The superclass of all three dimensional entities.
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class entity:public object3d,public renderable<object>, public moveable<object>, public node<entity>{
  public:
                  entity(void);
                 ~entity(void);
    
    void          setlife(int life);
    int           getlife(void);
    int           getage(void);
    
    void          setsize(float size);
    float         getsize(void);
    
    void          reset(void);

    bool          age(int life); 
    
    void          setcolor(float r, float g, float b,float alpha);
    void          setcolor(float r, float g, float b);
    
  
  protected:
    float         r,g,b,alpha;
    float         size;
  private:
    int           maxlife,curlife;    
  };
  
  class bone;
  class sphere;
  class line;
  class turtle;
  class skeleton;
  class terrain;
  class emitter;
  class entityfactory;
  class object3ds;
  class force;
  
  #include "line.h"
  #include "bone.h"
  #include "emitter.h"
  #include "entityfactory.h"
  #include "force.h"
  #include "sphere.h"
  #include "normals.h"
  #include "object3ds.h"  
  #include "skeleton.h"
  #include "terrain.h"
  #include "turtle.h"
  #include "particle.h"
  
#endif

