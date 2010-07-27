#include "3dsSupport.h"

// VBO Extension Function Pointers
PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;					// VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;					// VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;					// VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;	

bool Unbuffer3DS(const unsigned int buffer_num){
  return false;
}

bool Clean3DS(model_3ds* model){
  delete [] model->vertex;
  delete [] model->mapcoord;
  return true;
}

int findmaterial(model_3ds model, char* name){
  for(int x=0;x<model.num_materials;x++){
    if(strstr(model.materials[x].name,name)){
      return x;
    }
  }
  return 0;
}

void cleanBuffers(ApplicationInfo *application){
  for(int x=0;x<application->num_objects;x++){
    if(application->objects[x].buffered){
      glDeleteBuffersARB(1,&application->objects[x].VBOvertex);
      glDeleteBuffersARB(1,&application->objects[x].VBOcolor);
      application->objects[x].buffered=false;
    }
  }
}

bool Buffer3DS(model_3ds* model){
  printf("Buffering 3ds-file: %s\n",model->name);
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
  glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
	// Generate And Bind The Vertex Buffer
  GLuint  buffernum=0;
  GLfloat verticesunpacked[9*model->num_polygons];
  unsigned char colorunpacked[12*model->num_polygons];
 // GLfloat       normalsunpacked[3*model->num_polygons];
 // GLfloat       mapcoordsunpacked[6*model->num_polygons];
  printf("Generating vertexbuffer\n");
	glGenBuffersARB( 1, &buffernum );					// Get A Valid Name
  model->VBOvertex = buffernum;
  int cnt=0;
  for(int x=0;x<model->num_polygons;x++){
    for(int triside=0;triside<3;triside++){
      for(int sideloc=0;sideloc<3;sideloc++){
        int vertexnum = model->polygon[x].v[triside];
        if(vertexnum >= model->num_vertices){printf("Model %s contains incomplete polygon at %d\n",model->name,x);vertexnum=0;}
        verticesunpacked[cnt] = model->vertex[vertexnum].l[sideloc];
        cnt++;
      }
    }
  }
  glBindBufferARB( GL_ARRAY_BUFFER_ARB, model->VBOvertex );			// Bind The Buffer
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model->num_polygons*9*sizeof(GLfloat), verticesunpacked, GL_DYNAMIC_DRAW_ARB );
  free((void*)verticesunpacked);
  
  printf("Generating colorbuffer\n");
  glGenBuffersARB(1, &buffernum); 
  model->VBOcolor = buffernum;
  cnt=0;
  for(int x=0;x<model->num_polygons;x++){
    int matnum = findmaterial(*model,model->polygon[x].materialname);   //Find material for this edge
    for(int triside=0;triside<3;triside++){
      for(int color=0;color<4;color++){
        colorunpacked[cnt] = (unsigned char)model->materials[matnum].ambient[color];   //Set color
        cnt++;
      }
    }
  }
  printf("Done colors %d\n",model->VBOcolor);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, model->VBOcolor);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, model->num_polygons*12*sizeof(unsigned char), colorunpacked, GL_DYNAMIC_DRAW_ARB);
  
/*
	glGenBuffersARB( 1, &buffernum );					                            //Generate And Bind The Texture Coordinate Buffer Get A Valid Name
  model->VBOmapcoord = buffernum;
  cnt=0;  
  for(int x=0;x<model->num_polygons;x++){
    for(int triside=0;triside<3;triside++){
      mapcoordsunpacked[cnt] =   model->mapcoord[model->polygon[x].v[triside]].u;
      mapcoordsunpacked[cnt+1] = model->mapcoord[model->polygon[x].v[triside]].v;
      cnt=cnt+2;
    }
  }
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model->VBOmapcoord );		         // Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model->num_vertices*6*sizeof(float), mapcoordsunpacked, GL_STATIC_DRAW_ARB );
  */
  model->buffered=true;
  
  return model->buffered;
}

void loadModels(ApplicationInfo *application){
  application->num_objects=getnumfiles("data/Models",".3ds");
  application->objects = (model_3ds*)malloc(sizeof(model_3ds)*application->num_objects);
  for(int x=0;x< application->num_objects;x++){
    Load3DS(&(application->objects[x]),getfilename("data/Models",".3ds",x));
    Buffer3DS(&(application->objects[x]));
  }
  printf("Buffering done\n");
}

bool Load3DS (model_3ds* model,const char* filename){
  int i;
  int n_objects=0;int sum_verts=0;int sum_poly = 0;
  printf("Scanning 3ds-file: %s\n",filename);
  char materialname[20];
  char objectname[20];
  char r, g, b;
  FILE *file_3ds;
  unsigned short l_chunk_id;
  unsigned int l_chunk_length;
  unsigned char l_char;
  unsigned short l_qty, temp;
  unsigned short l_face_flags;
  bool is_diffuse, is_specular, is_ambient;
  sprintf(model->name,filename);
  model->loaded=false;
  model->buffered=false;
  model->num_vertices =0;
  model->num_polygons =0;
  model->num_materials=0;
  
  if ((file_3ds = fopen(filename, "rb"))== NULL) return false;  //Open the file
  while (ftell (file_3ds) < filelength (fileno (file_3ds))){    //Loop to scan the whole file 
    fread (&l_chunk_id, 2, 1, file_3ds);                        //Read the chunk header
    fread (&l_chunk_length, 4, 1, file_3ds);                    //Read the length of the chunk 
    switch (l_chunk_id)
    {
      case 0x4d4d: 
      break; 
      case 0x3d3d:
      break; 
      case 0x4000: 
      i=0;
      do{
        fread (&l_char, 1, 1, file_3ds);
        objectname[i]=l_char;
        i++;
      }while(l_char != '\0' && i<MAX_NAME);
      //printf("%s, ",objectname);
      n_objects++;
      break; 
      case 0x4100:
      break; 
      case 0x4110: 
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->num_vertices = l_qty;
        model->vertex = new vertex_type[model->num_vertices];
        //printf("Number of vertices: %d\n",l_qty);
        sum_verts += l_qty;
        for (i=0; i<l_qty; i++){
          fread (&model->vertex[i].l[0], sizeof(float), 1, file_3ds);
          fread (&model->vertex[i].l[1], sizeof(float), 1, file_3ds);
          fread (&model->vertex[i].l[2], sizeof(float), 1, file_3ds);                            
        }
      break; 
      case 0x4120:
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->num_polygons = l_qty;
        model->polygon = new polygon_type[model->num_polygons];
        //printf("Number of polygons: %d\n",l_qty);
        sum_poly += l_qty;        
        for (i=0; i<l_qty; i++){
          fread (&model->polygon[i].v[0], sizeof (unsigned short), 1, file_3ds);
          fread (&model->polygon[i].v[1], sizeof (unsigned short), 1, file_3ds);
          fread (&model->polygon[i].v[2], sizeof (unsigned short), 1, file_3ds);
          fread (&l_face_flags, sizeof (unsigned short), 1, file_3ds);
        }
      break; 
      case 0x4130:
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          materialname[i] = l_char;
          i++;
        }while(l_char != '\0' && i<MAX_NAME);
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);            
        for (i=0; i<l_qty; i++){
          fread (&temp, sizeof (unsigned short), 1, file_3ds);
          strcpy(model->polygon[temp].materialname,materialname);
        }
      break;
      case 0xAFFF:
      break;
      case 0xA000:
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          materialname[i] = l_char;
          i++;
        }while(l_char != '\0' && i<MAX_NAME);
        model->num_materials++;
        strcpy(model->materials[model->num_materials].name,materialname);
       break;       
       case 0xA010:
         is_diffuse = FALSE;
         is_specular = FALSE;
         is_ambient = TRUE;
       break;
       case 0xA020:   
        is_diffuse = TRUE;
        is_specular = FALSE;
        is_ambient = FALSE;
       break;

       case 0xA030: 
        is_diffuse = FALSE;
        is_specular = TRUE;
        is_ambient = FALSE;   
       break;
       case 0xA200:
       break;
       case 0xA300:
        i=0;
        do{
          fread (&l_char, 1, 1, file_3ds);
          materialname[i]= l_char;
          i++;
        }while(l_char != '\0' && i<MAX_NAME);
        strcpy(model->materials[model->num_materials].textureName,materialname);
        // printf("Texture: %s\n",model->materials[model->num_materials].textureName);
       break;
       case 0x0011:
        fread(&r, sizeof(char), 1, file_3ds); // Red component 1 byte
        fread(&g, sizeof(char), 1, file_3ds); // Green component 1 byte
        fread(&b, sizeof(char), 1, file_3ds); // Blue component 1 byte         
        if(is_diffuse){
          model->materials[model->num_materials].diffuse[0] = r;
          model->materials[model->num_materials].diffuse[1] = g;
          model->materials[model->num_materials].diffuse[2] = b;                            
        }else if(is_ambient){
          model->materials[model->num_materials].ambient[0] = r;
          model->materials[model->num_materials].ambient[1] = g;
          model->materials[model->num_materials].ambient[2] = b;  
        }else if(is_specular){
          model->materials[model->num_materials].specular[0] = r;
          model->materials[model->num_materials].specular[1] = g;
          model->materials[model->num_materials].specular[2] = b;  
        }       
      break;
      case 0x4140:
        fread (&l_qty, sizeof (unsigned short), 1, file_3ds);
        model->mapcoord = new mapcoord_type[model->num_vertices];
        for (i=0; i<l_qty; i++){
          fread (&model->mapcoord[i].u, sizeof (float), 1, file_3ds);
          fread (&model->mapcoord[i].v, sizeof (float), 1, file_3ds);
        }
      break;
      default:
        fseek(file_3ds, l_chunk_length-6, SEEK_CUR);
      break;
    } 
  } 
  fclose (file_3ds); // Closes the file stream
  model->loaded=true;
  printf("Model loaded into memory\nObjects: %d\tVerts: %d\tPoly: %d\n", n_objects, sum_verts, sum_poly);
  return model->loaded; // Returns ok
  } 
