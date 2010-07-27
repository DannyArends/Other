#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__
#include "includes.h"

#define PI 3.1415965

static const int MAX_MATERIALS = 20;
static const int MAX_LINES = 20;
static const int MAX_CHAR = 150;
static const int MAX_NAME = 20;
static const int MAX_COMMAND = 10;
static const int MAX_FILEPATH = 50;

typedef struct{
	const char*   name;
  GLuint	bpp;											  // Image Color Depth In Bits Per Pixel.
	GLuint	width,height;								// Image Dimensions
	GLuint	texID;											// Texture ID Used To Select A Texture
  GLuint	base;                       // Allows us to select subsquares 
} TextureImage;												// Structure Name

typedef struct{
	char* name;
  GLuint	bpp;											  // Image Color Depth In Bits Per Pixel.
	GLuint	width,height;								// Image Dimensions
  GLubyte	*mapData;									  // Image Data (Up To 32 Bits)
  GLuint DisplayList;
} map_type;

typedef struct{
	float x,y,z;
} Location;

typedef struct{
	float r,g,b;
	float alpha;
} RGBcolor;
 
typedef struct{
  GLfloat l[3];
}vertex_type;

typedef struct{
    char materialname[MAX_NAME];
    GLuint v[3];
}polygon_type;

typedef struct {
  char          name[MAX_NAME];    
	char          ambient[4];             // Ambient color (RGBA)
  char          diffuse[4];             // Diffuse color (RGBA)
  char          specular[4];            // Specular color (RGBA)
	char          textureName[MAX_NAME];
} material_type;

typedef struct {
  char name[MAX_NAME];
  char on_click[MAX_COMMAND];
  int x,y,l;
  bool on;
	char texturename[MAX_NAME];
} button_type;

typedef struct {
  int winid;
  int x,y,xl;
  bool on;
  char name[MAX_NAME];
  int num_buttons;
  button_type* buttons;
  int num_lines;
  char** lines;  
	char texturename[MAX_NAME];
} window_type;

typedef struct{
    float u,v;
}mapcoord_type;

typedef struct {
	char name[MAX_FILEPATH];
	bool loaded;
  bool buffered;
  int num_vertices;
  int num_polygons;
  int num_materials;
  
  vertex_type* vertex;  // RAM pointers
  polygon_type* polygon;
  mapcoord_type* mapcoord;
  material_type materials[MAX_MATERIALS];
  
	GLuint VBOvertex;   // Videocard VBO pointers
  GLuint VBOcolor;
	GLuint VBOpolygons;  
	GLuint VBOmapcoord;

} model_3ds, *model_3ds_ptr;

const RGBcolor RED      ={1.0f,0.0f,0.0f,1.0f};
const RGBcolor GREEN    ={0.0f,1.0f,0.0f,1.0f};
const RGBcolor BLUE     ={0.0f,0.0f,1.0f,1.0f};
const RGBcolor YELLOW   ={5.0f,5.0f,0.0f,1.0f};
const RGBcolor WHITE    ={1.0f,1.0f,1.0f,1.0f};
const RGBcolor GRAY     ={0.5f,0.5f,0.5f,1.0f};
const RGBcolor BLACK    ={0.0f,0.0f,0.0f,1.0f};

typedef double*  dvector;
typedef char*    cvector;
typedef int*     ivector;

typedef double** dmatrix;
typedef char**   cmatrix;
typedef int**    imatrix;

dvector newdvector(const unsigned int dim);
cvector newcvector(const unsigned int dim);
ivector newivector(const unsigned int dim);

void freevector(void *v);

dmatrix newdmatrix(const unsigned int rows, const unsigned int cols);
cmatrix newcmatrix(const unsigned int rows, const unsigned int cols);
imatrix newimatrix(const unsigned int rows, const unsigned int cols);

void printdmatrix(const dmatrix m, const unsigned int rows, const unsigned int cols);
void printcmatrix(const cmatrix m, const unsigned int rows, const unsigned int cols);
void printimatrix(const imatrix m, const unsigned int rows, const unsigned int cols);

void deldmatrix(dmatrix m, const unsigned int rows);
void delcmatrix(cmatrix m, const unsigned int rows);
void delimatrix(imatrix m, const unsigned int rows);

typedef struct{
  int           cur_char;
  char          textinput[MAX_CHAR];
  int           num_windows;
  window_type*  windows;
} hud_type;

typedef struct{
  float x,y,z;
  int angle_h,angle_v;
  bool locked;
}camera_type;

typedef struct{
  TCPsocket socket;
  IPaddress ip;
  int num_clients;
  SDLNet_SocketSet clients;
}ServerInfo;

typedef struct{
  int           num_textures;
  TextureImage* textures;
  int           num_objects;
  model_3ds*    objects;
  int           num_maps,c_map;
  map_type*     maps;
  ServerInfo    server;
  TCPsocket     client;
  int           font_texture;
  int           fps;
  hud_type      hud;
  camera_type   camera;
} ApplicationInfo;



#endif
