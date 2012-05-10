/**
 * \file GUI/universe.cpp
 * \brief Code file, Implementation of class: \ref universe
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "universe.h"

universe::universe(engine* e){
  cout << "[UNIVERSE]\tStarting up" << endl;
  this->myengine = e;
  this->myentities = new entityfactory(this);
  setupcamera();
  loadterrain();
  loadobjects();
  this->framecount=0;
  cout << "[UNIVERSE]\tLoaded all" << endl;
}

universe::~universe(void){

}

void universe::setupcamera(void){
  this->mycam = new camera();
}

/**
* \brief Move the camera<br>
* bugs: none found<br>
* @param x new x location of the camera<br>
* @param y new y location of the camera<br>
* @param z new z location of the camera<br>
*/
bool universe::movecamera(int x, int y, int z){
  this->mycam->movelocation(x,y,z);
  return true;
}

/**
* \brief Rotate the camera<br>
* bugs: none found<br>
* @param x new x rotation of the camera<br>
* @param y new y rotation of the camera<br>
* @param z new z rotation of the camera<br>
*/
bool universe::rotatecamera(int x, int y, int z){
  this->mycam->setrotation(x,y,z);
  return true;
}

/*
 * \brief Setup the viewport on the universe for navigation
 *
 *
 */
bool universe::setupviewport(void){
  GLfloat h = (GLfloat) myengine->getinfo()->height / (GLfloat) myengine->getinfo()->width;
  glViewport(0, 0, (GLint)  myengine->getinfo()->width, (GLint)  myengine->getinfo()->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -h, h, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  return(true);
}

/*
 * \brief Loads terrain from file olsmap.tga
 *
 * Should use myio to scan the directory for all 3ds objects and load them
 *
 */
void universe::loadterrain(void){
  this->map = new terrain();
  string maplocation = this->myengine->getinfo()->mapdir + "/olsmap.tga";
  map->LoadFromImage(maplocation.c_str(),1);
	map->ScaleHeights(0,2);
  map->setlight(100,1000,0,10);
  map->setlightcolorambient(0.2,0.2,0.2);
  map->setlightcolordiffuse(0.8,0.8,0.8);
  //map->setradius(80);
	map->SetOrigin((this->map->getxlength()/2),0,(this->map->getylength()/2));
  map->buffer(0,GL_TRIANGLE_STRIP);
  addchild(map);
}

/*
 * \brief Loads object from file humanoid.3ds
 *
 * Should use myio to scan the directory for all 3ds objects and load them
 *
 */
void universe::loadobjects(void){
  object3ds* o3d = new object3ds();
  string objectlocation = this->myengine->getinfo()->objectdir + "/Avatar_3.3ds";
  o3d->loadentity(objectlocation.c_str());
  if(o3d->buffer()) o3d->cleanentityRAM();
  addchild(o3d);
}

/*
 * \brief Returns a pointer to the engine
 *
 */
engine* universe::getengine(void){
  return this->myengine;
}

void universe::render(void){
  setupviewport();
  glPushMatrix(); 
  glLoadIdentity();
  glTranslatef(this->mycam->getx(),this->mycam->gety(),this->mycam->getz());
  glRotatef(this->mycam->getrotation(0), 1.0, 0.0, 0.0);
  glRotatef(this->mycam->getrotation(1), 0.0, 1.0, 0.0);
  glRotatef(this->mycam->getrotation(2), 0.0, 0.0, 1.0);
  vector<entity*> entities = getchildren();
  for(uint t=0;t<entities.size();t++){
    entities[t]->render();
    entities[t]->age(1);
  }
  this->mycam->update(1);
  glPopMatrix();
  glFlush();
  framecount++;
}
