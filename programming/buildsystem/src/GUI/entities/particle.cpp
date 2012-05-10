/**
 * \file GUI/entities/particle.cpp
 * \brief Code file, Implementation of class: \ref particle
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "particle.h"

particle::particle(void){

}

particle::~particle(void){

}

void particle::randomcolor(void){
	this->r=float(rand()%255)/255;
	this->g=float(rand()%255)/255;
	this->b=float(rand()%255)/255;
	this->alpha=1.0f;
}

void particle::render(void){
	glPushMatrix();
	glColor4f(this->r,this->g,this->b,this->alpha);
  float s=this->size;
	float xp=(this->getlocation()[0])+s;
	float yp=(this->getlocation()[1])+s;
	float zp=(this->getlocation()[2])+s;
	float xn=(this->getlocation()[0])-s;
	float yn=(this->getlocation()[1])-s;
	float zn=(this->getlocation()[2])-s;
	glBegin(GL_QUADS);									// Draw A Quad

		glVertex3f(xp,yp,zn);					// Top Right Of The Quad (Top)
		glVertex3f(xn,yp,zn);					// Top Left Of The Quad (Top)
		glVertex3f(xn,yp,zp);					// Bottom Left Of The Quad (Top)
		glVertex3f(xp,yp,zp);					// Bottom Right Of The Quad (Top)

		glVertex3f(xp,yn,zp);					// Top Right Of The Quad (Bottom)
		glVertex3f(xn,yn,zp);					// Top Left Of The Quad (Bottom)
		glVertex3f(xn,yn,zn);					// Bottom Left Of The Quad (Bottom)
		glVertex3f(xp,yn,zn);					// Bottom Right Of The Quad (Bottom)

		glVertex3f(xp,yp,zp);					// Top Right Of The Quad (Front)
		glVertex3f(xn,yp,zp);					// Top Left Of The Quad (Front)
		glVertex3f(xn,yn,zp);					// Bottom Left Of The Quad (Front)
		glVertex3f(xp,yn,zp);					// Bottom Right Of The Quad (Front)

		glVertex3f(xp,yn,zn);					// Top Right Of The Quad (Back)
		glVertex3f(xn,yn,zn);					// Top Left Of The Quad (Back)
		glVertex3f(xn,yp,zn);					// Bottom Left Of The Quad (Back)
		glVertex3f(xp,yp,zn);					// Bottom Right Of The Quad (Back)

		glVertex3f(xn,yp,zp);					// Top Right Of The Quad (Left)
		glVertex3f(xn,yp,zn);					// Top Left Of The Quad (Left)
		glVertex3f(xn,yn,zn);					// Bottom Left Of The Quad (Left)
		glVertex3f(xn,yn,zp);					// Bottom Right Of The Quad (Left)

		glVertex3f(xp,yp,zn);					// Top Right Of The Quad (Right)
		glVertex3f(xp,yp,zp);					// Top Left Of The Quad (Right)
		glVertex3f(xp,yn,zp);					// Bottom Left Of The Quad (Right)
		glVertex3f(xp,yn,zn);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad
	glPopMatrix();
}
