/**
 * \file GUI/entities/entityfactory.cpp
 * \brief Code file, Implementation of class: \ref widgetfactory
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "entityfactory.h"

entityfactory::entityfactory(universe* u){
  this->myuniverse = u;
  loadlocalmaps();
  loadlocal3ds();
}

bool entityfactory::loadlocal3ds(void){
  myio* io = this->myuniverse->getengine()->getfilesystem();
  string location = this->myuniverse->getengine()->getinfo()->objectdir;
  string objectlocation;
  vector<string> s = io->filesindir(location,"3ds");
  for(uint x=0;x<s.size();x++){
    cout << "[FACTORY3ds]\t" << s[x] << endl;
    object3ds* o3d = new object3ds();
    objectlocation = location + "/" + s[x];
    o3d->loadentity(objectlocation.c_str());
    if(o3d->buffer()) o3d->cleanentityRAM();
    addchild(o3d);
  }
  return true;
}

bool entityfactory::loadlocalmaps(void){
  myio* io = this->myuniverse->getengine()->getfilesystem();
  string location = this->myuniverse->getengine()->getinfo()->mapdir;
  string objectlocation;
  vector<string> s = io->filesindir(location,"tga");
  for(uint x=0;x<s.size();x++){
    cout << "[FACTORYmap]\t" << s[x] << endl;
    terrain* map = new terrain();
    objectlocation = location + "/" + s[x];
    map->LoadFromImage(objectlocation.c_str(),1);
    map->ScaleHeights(0,2);
    map->setlight(100,1000,0,10);
    map->setlightcolorambient(0.2,0.2,0.2);
    map->setlightcolordiffuse(0.8,0.8,0.8);
    map->SetOrigin((map->getxlength()/2),0,(map->getylength()/2));
    map->buffer(0,GL_TRIANGLE_STRIP);
    addchild(map);
  }
  return true;
}

bool entityfactory::loadremoteentities(void){
  return true;
}

entityfactory::~entityfactory(void){

}
