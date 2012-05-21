/**
 * \file GUI/entities/line.cpp
 * \brief Code file, Implementation of class: \ref line
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "line.h"

line::line(void): entity::entity(){

}

line::~line(void){

}

void line::setendlocation(float x, float y, float z){
  this->endlocation[0]=x;
  this->endlocation[1]=y;
  this->endlocation[2]=z;
}

void line::randomcolor(void){
	this->r=float(rand()%255)/255;
	this->g=float(rand()%255)/255;
	this->b=float(rand()%255)/255;
	this->alpha=1.0f;
}

void line::render(void){
	glPushMatrix();
	glColor4f(this->r,this->g,this->b,this->alpha);
	float xs=this->getx();
	float ys=this->gety();
	float zs=this->getz();
	float xe=this->endlocation[0];
	float ye=this->endlocation[1];
	float ze=this->endlocation[2];
	glBegin(GL_LINES);									// Draw A Quad
		glVertex3f(xs,ys,zs);					// Top Right Of The Quad (Top)
		glVertex3f(xe,ye,ze);					// Top Left Of The Quad (Top)
	glEnd();											// Done Drawing The Quad
	glPopMatrix();
}
