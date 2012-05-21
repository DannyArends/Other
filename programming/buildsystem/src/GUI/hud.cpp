/**
 * \file GUI/hud.cpp
 * \brief Code file, Implementation of class: \ref hud
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "hud.h"

hud::hud(engine* e,tgaInfo* fonttexture) : object2d::object2d(){
	this->myengine = e;
  this->font=fonttexture;
  this->initfont();
  window* w = new window(this);
  w->setlocation(100,100);
  addchild(w);
  mainmenu* m = new mainmenu(this);
  addchild(m);
}

hud::~hud(void){
  tgaDestroy(this->font);
	glDeleteLists(this->base,256);
  message("[HUD]\t\tFont deleted");
}

void hud::printinputline(void){
  glprint(0,myengine->getinfo()->height-25,0,(myengine->getscreenhandler())->getinputstring());
}

void hud::resize(void){
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = this->getchildren()[c];
    if(w->type==MAINMENUWIDGET){
      mainmenu* m = (mainmenu*)w;
      m->resize();
    }else{
      w->resize();
    }
  }
}

void hud::initfont(void){
  cout << "[HUD]\t\tFont (Type: " << (int)this->font->type << ") loaded with status "<< this->font->status << endl;
  cout << "[HUD]\t\tFont " << this->font->width << "x" << this->font->height << "@" << this->font->pixelDepth << endl;
  cout << "[HUD]\t\tStored with textureID: " << this->font->textureID << endl;
  this->base=glGenLists(256);
	glBindTexture(GL_TEXTURE_2D, this->font->textureID);
	for (int loop1=0; loop1<256; loop1++){
		float cx=float(loop1%16)/16.0f;						      // X Position Of Current Character
		float cy=float(loop1/16)/16.0f;						      // Y Position Of Current Character
		glNewList(base+loop1,GL_COMPILE);					      // Start Building A List
			glBegin(GL_QUADS);
				glTexCoord2f(cx,1.0f-cy-0.0625f);			        // Texture Coord (Bottom Left)
				glVertex2d(0,16);							                // Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	    // Texture Coord (Bottom Right)
				glVertex2i(16,16);							              // Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);	    // Texture Coord (Top Right)
				glVertex2i(16,0);							                // Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy-0.001f);		        	// Texture Coord (Top Left)
				glVertex2i(0,0);							                // Vertex Coord (Top Left)
			glEnd();
			glTranslated(14,0,0);							              // Move To The Right Of The Character
		glEndList();
	}
}

void hud::render(void){
  glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										      // Reset The Projection Matrix
	glOrtho(0.0f,(GLfloat)getwidth(),(GLfloat)getheight(),0.0f,-1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										      // Reset The Modelview Matrix
  for(uint c=0;c<this->getchildren().size();c++){
    widget* w = this->getchildren()[c];
    w->render();
  }
  printinputline();
  glFlush();
}

GLuint hud::getbase(void){
  return this->base;
}
GLuint hud::getfonttextureid(void){
  return this->font->textureID;
}

screenhandler* hud::getscreenhandler(void){
  return this->myengine->getscreenhandler();
}

cloudmember* hud::getcloudentry(void){
  return this->myengine->getapplication()->getcloudmember();
}

int hud::getwidth(void){
  return myengine->getinfo()->width;
}

int hud::getheight(void){
  return myengine->getinfo()->height;
}

GLvoid hud::glprint(GLint x, GLint y, int set, const char *fmt, ...){
	if (fmt == NULL)  return;
  
  char		text[1024];									// Holds Our String
	va_list ap;											// Pointer To List Of Arguments
	
  va_start(ap, fmt);										// Parses The String For Variables
	vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);												// Results Are Stored In Text

	if (set>1) set=1;												// If So, Select Set 1 (Italic)
  if (set<0) set=0;												// If So, Select Set 0 (normal)
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslated(x,y,0);									// Position The Text (0,0 - Top Left)
	glListBase(base-32+(128*set));							// Choose The Font Set (0 or 1)
	glScalef(1.0f,1.0f,1.0f);								// Make The Text 2X Taller
	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);		// Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping
}

void hud::deletefont(void){

}
