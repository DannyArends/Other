/**
 * \file GUI/entities/skeleton.cpp
 * \brief Code file, Implementation of class: \ref skeleton
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "skeleton.h"

skeleton::skeleton(void){

}

skeleton::~skeleton(void){

}

bool skeleton::buffer(void){
  if(this->displaylist)glDeleteLists(this->displaylist,1);
  this->displaylist = glGenLists(1);
  glNewList(this->displaylist,GL_COMPILE);
  printopengl();
  glEndList();
  this->setbuffered(true);
  return this->buffered;
}

void skeleton::printopengl(void){
  glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 0);
    glTexCoord2f( 0 , 0 );  
    glVertex3f(0, 0, 0);

    glNormal3f(0, 0, 0);
    glTexCoord2f( 0 , 0 );        
    glVertex3f(0, 0, 0);
    
    glNormal3f(0, 0, 0);
    glTexCoord2f( 0 , 0 );        
    glVertex3f(0, 0, 0);    
  glEnd();
}


void skeleton::render(void){
  glPushMatrix();
  glTranslatef((this->getlocation()[0]), (this->getlocation()[1]), (this->getlocation()[2]));
  if(this->isbuffered()){
    glCallList(this->displaylist);
  }else{
    printopengl();
  }
  glPopMatrix();
}
