/**
 * \file GUI/entities/emitter.h
 * \brief Header file, for GUI/entities/emitter.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef EMITTER_H_
  #define EMITTER_H_
  #include "ENTITIES.h"

  /** 
      * \brief Class representing a particle emitter.
      */
  class emitter : public taskholder, public entity{
  public:
    emitter();
  	~emitter(void);
    void createparticles(int num);
  	void setlocation(float x, float y,float z);
  	void setlife(int life);
    bool age(int life);
    bool addforce(force* f);
  	void setcolor(float r, float g, float b, float alpha);
  	void randomcolor(void);
    void randomsize(void);
  	void setsize(float size);
  	void render(void);
    void runtask(void);
  private:
  	int maxlife,curlife;
  	float size;
  	float r,g,b,alpha;
    bool  gravity;
    vector<force*> forces;
  };

#endif
