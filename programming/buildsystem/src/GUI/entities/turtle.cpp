/**
 * \file GUI/entities/turtle.cpp
 * \brief Code file, Implementation of class: \ref turtle
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "turtle.h"

/** 
* The turtle class draws a 3D trurtle graphic to the screen<br>
* Uses the LSystem class from base<br>
* bugs: none found
*/
turtle::turtle(void): entity::entity(){ 
  this->axiom = string("=#X");
  system.setState(axiom);
  system.addRule('B', "BMLM");
  system.addRule('I', "<MLMB>");
  system.addRule('X', "UMM_MILX");
  this->itteration=0;
  this->max_length=20000;
  this->storedloc[0]=0;
  this->storedloc[1]=0;
  this->storedloc[2]=0;
  system.iterate();
}

/** 
* bugs: none found
*/
turtle::~turtle(void){

}

/**
* Sets a randomcolor for the turtle<br>
* bugs: none found<br>
*/
void turtle::randomcolor(void){
	this->r=float(rand()%255)/255;
	this->g=float(rand()%255)/255;
	this->b=float(rand()%255)/255;
	this->alpha=1.0f;
}


/**
* Decodes the LSystem's string into GL_LINES<br>
* bugs: none found<br>
*/
void turtle::decode(void){
  this->hori_rot=0;
  this->vert_rot=0;
  this->hor_speed=1;
  this->vert_speed=1;
  string str = system.getState();
  float nx=0;
	float ny=0;
	float nz=0;
  glLineWidth(3.0f);
  for(uint c=0;c<str.length();c++){
    if(str[c]=='M'){
      double xRot = (float(hori_rot)/360.0)*2*PI;    //Math.toRadians is toRadians in Java 1.5 (static import)
      double yRot = (float(vert_rot)/360.0)*2*PI;

      glColor4f(float(c)/float(this->max_length),1.0-(float(2*c)/float(this->max_length)),0.5-float(c)/float(2*this->max_length),this->alpha);
      glBegin(GL_LINES);									// Draw A Quad
      glVertex3f(nx,ny,nz);					// Top Right Of The Quad (Top)
      nx += (sin(xRot));
      ny += (-cos(xRot)*sin(yRot));
      nz += (cos(xRot)*cos(yRot));
      glVertex3f(nx,ny,nz);					// Top Right Of The Quad (Top)
      glEnd();											// Done Drawing The Quad  
    }
    if(str[c]=='+'){
      hor_speed=(hor_speed+int(str[c+1]))%360;
      c++;
    }
    if(str[c]=='-'){
      hor_speed=(hor_speed-int(str[c+1]))%360;
      c++;
    }
    if(str[c]=='='){
      vert_speed=(vert_speed+int(str[c+1]))%360;
      c++;
    }
    if(str[c]=='_'){
      vert_speed=(vert_speed-int(str[c+1]))%360;
      c++;
    }    
    if(str[c]=='L'){
      hori_rot=(hori_rot-hor_speed)%360;
    }
    if(str[c]=='R'){
      hori_rot=(hori_rot+hor_speed)%360;
    }    
    if(str[c]=='U'){
      vert_rot=(vert_rot-vert_speed)%360;
    }    
    if(str[c]=='D'){
      vert_rot=(vert_rot+vert_speed)%360;
    }
    if(str[c]=='<'){
      this->storedloc[0]=nx;
      this->storedloc[1]=ny;
      this->storedloc[2]=nz;
    }
    if(str[c]=='>'){
      nx=this->storedloc[0];
      ny=this->storedloc[1];
      nz=this->storedloc[2];
    }
    if(str[c]=='O'){
      nx=this->getx();
    	ny=this->gety();
    	nz=this->getz();
    }    
  }
	
}

/**
* Rendering routine for the turtle<br>
* bugs: none found<br>
*/
void turtle::render(void){
  if(system.getState().length() < this->max_length){
    system.iterate();
  }else{
    system.setState(axiom);
  }
  
	glPushMatrix();
  glTranslatef((this->getlocation()[0]), (this->getlocation()[1]), (this->getlocation()[2]));
	decode();
	glPopMatrix();
}
