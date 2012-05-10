/**
 * \file GUI/entities/emitter.cpp
 * \brief Code file, Implementation of class: \ref emitter
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#include "emitter.h"

/**
* Particle emitter class, used to tie particles and forces together<br>
* bugs: none found<br>
*/
emitter::emitter(){
  printf("[EMITTER]\n");
  this->r=0.0f;
  this->g=0.0f;
  this->b=0.0f;  
  this->alpha=0.0f;  
  this->size=0.01f;
	this->maxlife = 0;
  this->curlife = 0;
}

/**
* Create a fixed number of particles, lifespan of particles is set from 1 .. num+1<br>
* bugs: none found<br>
* @param num number of particles to create (is also used to set the lifespan)<br>
*/
void emitter::createparticles(int num){
  particle* p;
  for(int x=0;x<num;x++){
    p = new particle();
    p->setlife(x+1);
    addchild(p);
  }
}

/**
* bugs: none found<br>
*/
emitter::~emitter(void){

}

/**
* Set location of the particle emitter, also all particles are forced to this location<br>
* bugs: none found<br>
* @param x new x location of the emitter<br>
* @param y new y location of the emitter<br>
* @param z new z location of the emitter<br>
*/
void emitter::setlocation(float x, float y,float z){
  entity::setlocation(x,y,z);
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->setlocation(x,y,z);
  }
}

/**
* Sets the lifetime of particles emitted by this emitter<br>
* bugs: none found<br>
* @param life lifespan value (is relative to the age calls)<br>
*/
void emitter::setlife(int life){
  this->maxlife=life;
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->setlife((int)(life+(float(rand()%life))));
  }
}

/**
* Ages the particles emitted by this emitter<br>
* bugs: none found<br>
* @param life value deduced from lifespan of particles<br>
*/
bool emitter::age(int life){
  
  for(uint f=0;f<this->forces.size();f++){
    this->forces[f]->age(life);
  }
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    if(!entities[t]->age(life)){
      entities[t]->reset();
      entities[t]->setlocation(this->getx(),this->gety(),this->getz());  
    }
  }
  return true;
}

/**
* Adds a force to the particles<br>
* bugs: none found<br>
* @param f force to add to the particles emitted<br>
*/
bool emitter::addforce(force* f){
  printf("[EMITTER]\tNew force\n");
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    f->addchild(entities[t]);  
  }
  this->forces.push_back(f);
  return true;
}

/**
* Color all the particles<br>
* bugs: none found<br>
* @param r amount of red 0 to 1<br>
* @param g amount of green 0 to 1<br>
* @param b amount of blue 0 to 1<br>
* @param alpha alpha value<br>
*/
void emitter::setcolor(float r, float g, float b, float alpha){
  if(r>0) this->r=r;
  if(g>0) this->g=g;
  if(b>0) this->b=b;  
  this->alpha=alpha;
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->setcolor(r, g, b, alpha);
  }  
}

/**
* Random color per particle<br>
* bugs: none found<br>
*/
void emitter::randomcolor(void){
	this->alpha=1.0f;
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->setcolor(float(rand()%255)/255, float(rand()%255)/255, float(rand()%255)/255, this->alpha);
  }    
}

/**
* Random size per particle<br>
* bugs: none found<br>
*/
void emitter::randomsize(void){
	this->alpha=1.0f;
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    float s = float((rand()%1000)/2000.0f);
    entities[t]->setsize(s);
    entities[t]->setcolor(1-(s*2),(s*2),(s*2), this->alpha);
  }    
}

/**
* Fixed size per particle<br>
* bugs: none found<br>
* @param size size in openGL units<br>
*/
void emitter::setsize(float size){
  this->size=size;
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->setsize(size);
  }
}

/**
* The runtask routine is a need to overwrite from taskmanager, since this is a threadable job<br>
* bugs: none found<br>
* Here we use it to just set all particles to a different random color<br>
*/
void emitter::runtask(void){
  printf("%f\n",float(rand()%255)/255);
  setcolor(float(rand()%255)/255, float(rand()%255)/255, float(rand()%255)/255,1.0);
}

/**
* Renders the emitter<br>
* bugs: none found<br>
*/
void emitter::render(void){
  //this->age(1);
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->render();
  }
}
