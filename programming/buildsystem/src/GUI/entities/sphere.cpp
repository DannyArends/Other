/**
 * \file GUI/entities/sphere.cpp
 * \brief Code file, Implementation of class: \ref sphere
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "sphere.h"

sphere::sphere(void){
  this->size      = 0.0f;
  this->p         = 20;
  this->twopi     = 6.28318530717958f;
  this->pidtwo    = 1.57079632679489f;
  this->surface=0;
}

sphere::~sphere(void){

}

void sphere::setradius(float radius){
  this->size=radius;
}

void sphere::setprecision(uint p){
  this->p=p;
}

bool sphere::buffer(void){
  if(!this->size && !this->p){
    this->setbuffered(false);
  }else{
    if(this->displaylist)glDeleteLists(this->displaylist,1);
    this->displaylist = glGenLists(1);
    glNewList(this->displaylist,GL_COMPILE);
    printopengl();
    glEndList();
    this->setbuffered(true);
  }
  return this->isbuffered();
}

void sphere::addterrain(terrain* t){
  float l=float(min(t->getxlength(),t->getylength()));
  this->surface=t;
  this->p=(uint)(l-3);
  this->size=float(l/2);
  this->surface->ScaleHeights(0,l/15);
}

force* sphere::getgravity(void){
  this->gravity = new force();
  //printf("sph:%f %f %f\n",this->location[0],this->location[1],this->location[2]);
  //this->gravity->setlocation((this->getlocation()[0]), (this->getlocation()[1]), (this->getlocation()[2]));
  this->gravity->setparent(this);
  return this->gravity;
}


void sphere::printopengl(void){
  float theta1,theta2,theta3;
  float ex,ey,ez;
  float px,py,pz;
  uint tsum = 0;
  uint ssum = 0;
  float si;
  float newradius;
  for(uint i = 0; i <= p; i++ ){
    glBegin(GL_TRIANGLE_STRIP);
    ssum++;
    si = float(i)/2.0;
    theta1 = si * twopi / p - pidtwo;
    theta2 = (si + 1) * twopi / p - pidtwo;
    for(uint j = 0; j <= p; j++ ){
      tsum++;
      theta3 = (p-j) * twopi / p;
      ex = cosf(theta2) * cosf(theta3);
      ey = sinf(theta2);
      ez = cosf(theta2) * sinf(theta3);
      if(this->surface){
        this->surface->setGLcolor(i+1,j);
        newradius = float((this->surface->getheight(i+1,j) + this->size));
        px = newradius * ex;
        py = newradius * ey;
        pz = newradius * ez;
      }else{
        glColor3f(float(i*2)/float(p),float(j)/float(p),1-float(j)/float(p));
        px = this->size * ex;
        py = this->size * ey;
        pz = this->size * ez;
      }
      
      
      glNormal3f(ex, ey, ez);
      glTexCoord2f( -(j/(float)p) , 2*(i+1)/(float)p );  
      glVertex3f(px, py, pz);
      
      ex = cosf(theta1) * cosf(theta3);
      ey = sinf(theta1);
      ez = cosf(theta1) * sinf(theta3);
      if(this->surface){
        this->surface->setGLcolor(i,j);
        newradius = float((this->surface->getheight(i,j) + this->size));
        px = newradius * ex;
        py = newradius * ey;
        pz = newradius * ez;
      }else{
        px = this->size * ex;
        py = this->size * ey;
        pz = this->size * ez;
      }

      glNormal3f(ex, ey, ez);
      glTexCoord2f( -(j/(float)p) , 2*(i+1)/(float)p );        
      glVertex3f(px, py, pz);
    }
    glEnd();
  }
}

void sphere::render(void){
  glPushMatrix();
  //glColor4f(this->r,this->g,this->b,this->alpha);
  glTranslatef((this->getlocation()[0]), (this->getlocation()[1]), (this->getlocation()[2]));
  if(this->isbuffered()){
    glCallList(this->displaylist);
  }else{
    printopengl();
  }
  glPopMatrix();
}
