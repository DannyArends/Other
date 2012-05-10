/**
 * \file GUI/entities/object3ds.cpp
 * \brief Code file, Several routines to handle 3ds files
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "object3ds.h"
// VBO Extension Definitions, From glext.h
#define GL_ARRAY_BUFFER_ARB               0x8892
#define GL_STATIC_DRAW_ARB                0x88E4
#define GL_DYNAMIC_DRAW_ARB               0x88E8
#define GL_DYNAMIC_READ_ARB               0x88E9
#define GL_DYNAMIC_COPY_ARB               0x88EA

typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);

PFNGLGENBUFFERSARBPROC pglGenBuffersARB = 0;                     // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC pglBindBufferARB = 0;                     // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC pglBufferDataARB = 0;                     // VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB = 0;               // VBO Deletion Procedure

#define glGenBuffersARB           pglGenBuffersARB
#define glBindBufferARB           pglBindBufferARB
#define glBufferDataARB           pglBufferDataARB
#define glDeleteBuffersARB        pglDeleteBuffersARB

object3ds::object3ds(){
  loaded=false;
}

object3ds::~object3ds(){

}

bool object3ds::cleanentityRAM(void){
  if(!this->isbuffered() && !loaded) return false;
  for(uint m=0;m<objects.size();m++){
    trianglelist* model = objects[m];
    free((void*)model->vertex);
    free((void*)model->polygon);
    free((void*)model->mapcoord);
  }
  loaded=false;
  return true;
}

int object3ds::findmaterial(char* name){
  for(uint x=0;x<materials.size();x++){
    if(strstr(materials[x]->name,name)){
      return x;
    }
  }
  return 0;
}

void object3ds::cleanentityVID(void){
  if(this->isbuffered()){
    glDeleteBuffersARB(1,&VBOvertex);
    glDeleteBuffersARB(1,&VBOcolor);
    this->setbuffered(false);
  }
}


void object3ds::render(void){
  float x= this->getx();
  float y= this->gety();
  float z= this->getz();
  if(this->isbuffered()){
    glEnableClientState(GL_VERTEX_ARRAY);                     // activate vertex coords array
    glEnableClientState(GL_COLOR_ARRAY);
   // glEnableClientState(GL_TEXTURE_COORD_ARRAY);				      // Disable Texture Coord Arrays
    
    glBindBufferARB( GL_ARRAY_BUFFER_ARB , VBOvertex);    // for vertex coordinates
    glVertexPointer( 3, GL_FLOAT, 0,0 );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB , VBOcolor);     // colors
    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, 0);
   // glBindBufferARB( GL_ARRAY_BUFFER_ARB , entity.VBOmapcoord);  // mapping coordingates
   // glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
    glPushMatrix();
      glTranslatef(x, y, z);
      glScalef(  0.1f,  0.1f, 0.1f);
      glRotatef( 90.0f,-1.0f, 0.0f, 0.0f);
      glDrawArrays( GL_TRIANGLES , 0 , 3*npolygons);     //There are 3 times more vertices in memory
    glPopMatrix(); 

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    
    glDisableClientState( GL_VERTEX_ARRAY );				        // Disable Vertex Arrays
    glDisableClientState( GL_COLOR_ARRAY );                 //Disable Color arrays
   // glDisableClientState( GL_TEXTURE_COORD_ARRAY );				  // Disable Texture Coord Arrays
  }else{
    if(!loaded){printf("entity not loaded");return;}
      int materialnum;
      int vertexnum;
      for(uint m=0;m<objects.size();m++){
        glPushMatrix();
        trianglelist* model = objects[m];
        glTranslatef(x, y, z);
        glScalef(  0.1f,  0.1f, 0.1f);
        glRotatef( 90.0f,-1.0f, 0.0f, 0.0f);  
        for(int x=0;x<model->npolygons;x++){
          float     triangle[3][3];
          float*    normal;

          for(int triside=0;triside<3;triside++){
            for(int sideloc=0;sideloc<3;sideloc++){
              vertexnum = model->polygon[x].p[triside];
              triangle[triside][sideloc] = model->vertex[vertexnum].v[sideloc];
            }
          }

          materialnum = findmaterial(model->polygon[x].materialname);
          materialtype* material = materials[materialnum];
          glColor3f(material->ambient[0]/256.0f,  material->ambient[1]/256.0f,  material->ambient[2]/256.0f);

          normal = trianglefindnormal(triangle);
          glBegin(GL_TRIANGLES);
          glNormal3f(normal[0], normal[1], normal[2]);
          glTexCoord2f(model->mapcoord[model->polygon[x].p[0]].u,model->mapcoord[model->polygon[x].p[0]].v);
          glVertex3f(triangle[0][0],triangle[0][1],triangle[0][2]); //Vertex definition

          glTexCoord2f(model->mapcoord[model->polygon[x].p[1]].u,model->mapcoord[model->polygon[x].p[1]].v);
          glVertex3f(triangle[1][0],triangle[1][1],triangle[1][2]); //Vertex definition

          glTexCoord2f(model->mapcoord[model->polygon[x].p[2]].u,model->mapcoord[model->polygon[x].p[2]].v);
          glVertex3f(triangle[2][0],triangle[2][1],triangle[2][2]); //Vertex definition
          glEnd();
          free((void*) normal);
        }
      }
      glPopMatrix();

  }
}

bool object3ds::buffer(void){
 // get pointers to GL functions
  if(!this->loaded){
    this->setbuffered(false);
    return this->isbuffered();
  }
  #ifdef WINDOWS
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
  #else
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)glXGetProcAddress((const unsigned char*)"glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC)glXGetProcAddress((const unsigned char*)"glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC)glXGetProcAddress((const unsigned char*)"glBufferDataARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)glXGetProcAddress((const unsigned char*)"glDeleteBuffersARB");
  #endif
   // check once again VBO extension

  if(glGenBuffersARB && glBindBufferARB && glBufferDataARB &&  glDeleteBuffersARB){
    printf("[3dsBUFFER]\tVideo card supports GL_ARB_vertex_buffer_object\n");
  }else{
    printf("[3dsBUFFER]\tVideo card does NOT support GL_ARB_vertex_buffer_object\n");
    return false;
  }

	// Generate And Bind The Vertex Buffer
  GLuint  buffernum=0;
  GLfloat verticesunpacked[9*npolygons];
  unsigned char colorunpacked[12*npolygons];
  //GLfloat       normalsunpacked[3*npolygons];
  //GLfloat       mapcoordsunpacked[6*npolygons];
  printf("[3dsBUFFER]\tGenerating vertexbuffer\n");
	glGenBuffersARB( 1, &buffernum );					// Get A Valid Name
  VBOvertex = buffernum;
  int cnt=0;
  for(uint m=0;m<objects.size();m++){
    trianglelist* model = objects[m];
    for(int x=0;x<model->npolygons;x++){
      for(int triside=0;triside<3;triside++){
        //printf("[3dsBUFFER]\tModel %s polygon %d %d->%d\n",model->name,x,triside,model->polygon[x].p[triside]);        
        for(int sideloc=0;sideloc<3;sideloc++){
          int vertexnum = model->polygon[x].p[triside];
          if(vertexnum >= model->nvertices){printf("[3dsBUFFER]\tModel %s contains incomplete polygon at %d\n",model->name,x);vertexnum=1;}
          verticesunpacked[cnt] = model->vertex[vertexnum].v[sideloc];
          cnt++;
        }
      }
    }
  }
  printf("[VERTEXBUFFER]\tIn RAM Buffer: %d\n[VERTEXBUFFER]\tAllocated on Videocard: %d/%d\n",cnt,9*npolygons,(cnt-(9*npolygons))/9);
  glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOvertex );			// Bind The Buffer
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, npolygons*9*sizeof(GLfloat), verticesunpacked, GL_DYNAMIC_DRAW_ARB );
  
  glGenBuffersARB(1, &buffernum); 
  VBOcolor = buffernum;
  cnt=0;
  for(uint m=0;m<objects.size();m++){
    trianglelist* model = objects[m];
    for(int x=0;x<model->npolygons;x++){
      int matnum = findmaterial(model->polygon[x].materialname);   //Find material for this edge
      for(int triside=0;triside<3;triside++){
        for(int color=0;color<4;color++){
          colorunpacked[cnt] = (unsigned char)materials[matnum]->ambient[color];   //Set color
          cnt++;
        }
      }
    }
  }
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBOcolor);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, npolygons*12*sizeof(unsigned char), colorunpacked, GL_DYNAMIC_DRAW_ARB);
  this->setbuffered(true);
  printf("[3dsBUFFER]\tBuffering done\n");
  return this->isbuffered();
}

trianglelist* createobject(char name[NAMESIZE]){
  trianglelist* model = new trianglelist();
  strcpy(model->name,name);
  model->nvertices =0;
  model->npolygons =0;
  return model;
}

materialtype* creatematerial(char name[NAMESIZE]){
  materialtype* material = new materialtype();
  strcpy(material->name,name);
  return material;
}

bool object3ds::loadentity(const char* filename){
  int i;
  int sum_verts=0;
  int sum_poly = 0;
  printf("[3dsLOAD]\tOpening 3ds-file: %s\n",filename);
  char materialname[NAMESIZE];
  char objectname[NAMESIZE];
  char texturename[NAMESIZE];
  char r, g, b;
  FILE *file_3ds;
  unsigned short l_chunk_id;
  unsigned int l_chunk_length;
  unsigned char l_char;
  unsigned short l_qty, temp;
  unsigned short l_face_flags;
  bool is_diffuse, is_specular, is_ambient;
  trianglelist* model = NULL;
  materialtype* material = NULL;
  if ((file_3ds = fopen(filename, "rb"))== NULL) return false;  //Open the file
  fseek(file_3ds, 0, SEEK_END);
  int filelength = ftell(file_3ds);
  fseek(file_3ds, 0, SEEK_SET);
  cout << "[3dsLOAD]\tLength of " << filename << ": " << filelength <<endl;
  while (ftell (file_3ds) < filelength){    //Loop to scan the whole file
    fread (&l_chunk_id, 2, 1, file_3ds);                        //Read the chunk header
    fread (&l_chunk_length, 4, 1, file_3ds);                    //Read the length of the chunk
    //printf("a %d\n",l_chunk_id);
    switch (l_chunk_id){
      case 0x4d4d: 
      break; 
      case 0x3d3d:
      break; 
      case 0x4000:
      //printf("4000\n");
      i=0;
      do{
        fread (&l_char, 1, 1, file_3ds);
        objectname[i]=l_char;
        i++;
      }while(l_char != '\0' && i<NAMESIZE);
      //printf("model %d\n",model);
      if(model != 0)  objects.push_back(model);
      model = createobject(objectname);
      break; 
      case 0x4100:
      break; 
      case 0x4110: 
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->nvertices = l_qty;
        model->vertex = new vertextype[model->nvertices];
        //printf("[3dsLOAD]\t %s Number of vertices: %d\n",objectname,l_qty);
        for (i=0; i<l_qty; i++){
          fread (&model->vertex[i].v[0], sizeof(float), 1, file_3ds);
          fread (&model->vertex[i].v[1], sizeof(float), 1, file_3ds);
          fread (&model->vertex[i].v[2], sizeof(float), 1, file_3ds);                            
        }
        sum_verts += l_qty;
      break; 
      case 0x4120:
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->npolygons = l_qty;
        model->polygon = new polygontype[model->npolygons];
        for (i=0; i<l_qty; i++){
          fread (&model->polygon[i].p[0], sizeof (unsigned short), 1, file_3ds);
          fread (&model->polygon[i].p[1], sizeof (unsigned short), 1, file_3ds);
          fread (&model->polygon[i].p[2], sizeof (unsigned short), 1, file_3ds);
          fread (&l_face_flags, sizeof (unsigned short), 1, file_3ds);
          //printf("[3dsLOAD]\t %s %d %d %d\n",model->name,model->polygon[i].p[0],model->polygon[i].p[1],model->polygon[i].p[2]);
        }
        sum_poly += l_qty;
      break; 
      case 0x4130:
        //printf("4130\n");
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          materialname[i] = l_char;
          i++;
        }while(l_char != '\0' && i<NAMESIZE);
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);            
        for (i=0; i<l_qty; i++){
          fread (&temp, sizeof (unsigned short), 1, file_3ds);
          strcpy(model->polygon[temp].materialname,materialname);
        }
      break;
      case 0xAFFF:
      break;
      case 0xA000:
        //printf("A000\n");
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          materialname[i] = l_char;
          i++;
        }while(l_char != '\0' && i<NAMESIZE);
        if(material != NULL) materials.push_back(material);
        material = creatematerial(materialname);
        //printf("Material_I: %s\n",materialname);
       break;       
       case 0xA010:
         is_diffuse = false;
         is_specular = false;
         is_ambient = true;
       break;
       case 0xA020:   
        is_diffuse = true;
        is_specular = false;
        is_ambient = false;
       break;
       case 0xA030: 
        is_diffuse = false;
        is_specular = true;
        is_ambient = false;   
       break;
       case 0xA200:
       break;
       case 0xA300:
        //printf("A300\n");
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          texturename[i]= l_char;
          i++;
        }while(l_char != '\0' && i<NAMESIZE);
        strcpy(material->texture,texturename);
        //printf("TEXTURE: %s\n",materialname);
       break;
       case 0x0011:
        //printf("0011\n");
        fread(&r, sizeof(char), 1, file_3ds); // Red component 1 byte
        fread(&g, sizeof(char), 1, file_3ds); // Green component 1 byte
        fread(&b, sizeof(char), 1, file_3ds); // Blue component 1 byte         
        if(is_diffuse){
          material->diffuse[0] = (int)r;
          material->diffuse[1] = (int)g;
          material->diffuse[2] = (int)b;
        }else if(is_ambient){
          material->ambient[0] = (int)r;
          material->ambient[1] = (int)g;
          material->ambient[2] = (int)b;
        }else if(is_specular){
          material->specular[0] = (int)r;
          material->specular[1] = (int)g;
          material->specular[2] = (int)b;
        }       
      break;
      case 0x4140:
        //printf("4140\n");
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->mapcoord = new mapcoordtype[model->nvertices];
        for (i=0; i<l_qty; i++){
          fread (&model->mapcoord[i].u, sizeof (float), 1, file_3ds);
          fread (&model->mapcoord[i].v, sizeof (float), 1, file_3ds);
        }
      break;
      default:
        //printf("DEF\n");
        fseek(file_3ds, l_chunk_length-6, SEEK_CUR);
      break;
    } 
  } 
  //printf("beforeclose\n");
  fclose (file_3ds); // Closes the file stream
  if(model != NULL) objects.push_back(model);
  if(material != NULL) materials.push_back(material);
  loaded=true;
  npolygons=sum_poly;
  nvertices=sum_verts;
  printf("[3dsLOAD]\tFile: %s loaded into memory\n[3dsLOAD]\tObjects: %d\tVerts: %d\tPoly: %d\n",filename, objects.size(), sum_verts, sum_poly);
  return loaded; // Returns ok
}
