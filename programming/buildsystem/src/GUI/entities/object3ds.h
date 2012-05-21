/**
 * \file GUI/entities/object3ds.h
 * \brief Header file, for GUI/object3ds.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef OBJECT3DS_H_
  #define OBJECT3DS_H_
  #include "ENTITIES.h"
  
 /** 
      * \brief Three dimensional 3ds object
      */      
  class object3ds: public bufferable<entity>{
  public:
    object3ds();
    ~object3ds();
    bool cleanentityRAM(void);
    void cleanentityVID(void);
    bool loadentity(const char *filename);
    bool buffer(void);
    void render(void);
  private:  
    int findmaterial(char* name);
    int           nvertices,npolygons;
    
    vector<trianglelist*>  objects;
    vector<materialtype*>  materials;

    bool          loaded;

    GLuint        VBOvertex;           // Videocard pointers
    GLuint        VBOcolor;
  	GLuint        VBOpolygons;  
  	GLuint        VBOmapcoord;
  };

#endif
