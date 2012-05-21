/**
 * \file GUI/entities/bone.cpp
 * \brief Code file, Implementation of class: \ref bone
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "bone.h"

bone::bone(void){
  this->orientation[0]  =0.0f;
  this->orientation[1]  =0.0f;
  this->orientation[2]  =0.0f;  
  this->buffered=false;
}

bone::~bone(void){

}

void bone::setorientation(float x,float y,float z){
  this->orientation[0]  =x;
  this->orientation[1]  =y;
  this->orientation[2]  =z; 
}

void bone::setlength(float l){
  this->length=l;
}

float bone::getlength(void){
 return this->length;
}


bool bone::buffer(void){
  if(this->displaylist)glDeleteLists(this->displaylist,1);
  this->displaylist = glGenLists(1);
  glNewList(this->displaylist,GL_COMPILE);
  printopengl();
  glEndList();
  this->buffered=true;
  return this->buffered;
}


void bone::printopengl(void){
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


void bone::render(void){
  glPushMatrix();
  glTranslatef((this->getlocation()[0]), (this->getlocation()[1]), (this->getlocation()[2]));
  if(this->buffered){
    glCallList(this->displaylist);
  }else{
    printopengl();
  }
  glPopMatrix();
}
