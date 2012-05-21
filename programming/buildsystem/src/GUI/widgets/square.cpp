/**
 * \file GUI/widgets/square.cpp
 * \brief Code file, Implementation of class: \ref square
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "square.h"

square::square() : widget::widget(){
  this->type=SQUAREWIDGET;
  this->color=WHITE;
}

void square::init(){

}

void square::render(void){
  glPushMatrix();
	glColor3f(color.r,color.g,color.b);
 	int xp=this->getx()+this->getsizex();
	int yp=this->gety()+this->getsizey();
  glBegin(GL_QUADS);
		glVertex3f(this->getx(), yp,  0.0f);
		glVertex3f(xp, yp,  0.0f);
		glVertex3f(xp, this->gety(),  0.0f);
		glVertex3f(this->getx(), this->gety(),  0.0f);
	glEnd();
  glPopMatrix();
}
