/**
 * \file GUI/GUI.h
 * \brief Header file, for the GUI directory
 *
 * This class is used to share the objects within the GUI directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * - \ref engine<br>
 * - \ref entity<br>
 * - \ref emitter<br>
 * - \ref hud<br>
 * - \ref force<br>
 * - \ref terrain<br>
 * - \ref widget<br>
 * - \ref particle<br>
 * - \ref universe<br>
 * - \ref screenhandler<br>
 *  
 **/

#ifndef GUI_H_
  #define GUI_H_
  #include "includes.h"
  #include "application.h"
  #include "NETWORK/NETWORK.h"

  //ALL DEPENDENCIES FOR THIS LIBRARY
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glext.h>
  #ifndef WINDOWS
    #include <GL/glx.h>
    #include <GL/glxext.h>
  #endif
  #include <SDL/SDL.h>

  
  //Structs and enums we define in this package
  #define BPP 4
  #define DEPTH 32
  
  /**
   * \brief engine info holding basic information for the 3D engine
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct engineinfo{
      int             width,height,bpp;
      string          texturedir,objectdir,mapdir;
  }engineinfo;

  /**
   * \brief Structure holding .TGA file information
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct tgaInfo{
  	int             status;
    GLuint          textureID;
    short int       width, height;
  	unsigned char   type, pixelDepth;
  	unsigned char*  imageData;
  } tgaInfo;
  
  /**
   * \brief Structure holding a vertex with associated boneID
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct vertextype{
    int boneID;
    float v[3];
  } vertextype;

  /**
   * \brief Structure holding a polygon with associated materialname
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct polygontype{
    char                materialname[NAMESIZE];
    unsigned short int  p[3];
  } polygontype;

  /**
   * \brief Structure u,v coordinates used in texturing
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  struct mapcoordtype{
    float u,v;
  };
  
  /**
   * \brief Structure holding material information
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  struct materialtype{
    char          name[NAMESIZE];
  	int           ambient[4];             // Ambient color (RGBA)
    int           diffuse[4];             // Diffuse color (RGBA)
    int           specular[4];            // Specular color (RGBA)
  	char          texture[NAMESIZE];
  };
  
  /**
   * \brief Structure holding a named and numbered triangle list
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  struct trianglelist{
  	char          name[NAMESIZE];
  	int           nvertices,npolygons;
    
    vertextype*   vertex;         // RAM pointers
    polygontype*  polygon;
    mapcoordtype* mapcoord;
  };
  
 /** 
  * \brief Virtual renderable class, all renderable things should inherit from this class.
  */
  template<class objecttype>       
  class renderable : public objecttype{
    public:
     /** 
      * Virtual function to needs overwriting to render the object<br>
      * bugs: none found
      */
                    renderable(){
                    }
      virtual       ~renderable(){
                    }
      virtual void  render(void){
                    }
    private:
  };

  class camera;
  class entity;
  class engine;
  class entityfactory;
  class emitter;
  class force;
  class hud;
  class force;
  class terrain;
  class widget;
  class particle;
  class universe;
  class screenhandler;

  //Share the objects
  #include "camera.h"
  #include "hud.h"
  #include "engine.h"
  #include "screenhandler.h"
  #include "tga.h"
  #include "universe.h"

  #include "widgets/WIDGETS.h"
  #include "entities/ENTITIES.h"

#endif
