#include "OpenGL.h"

// VBO Extension Function Pointers
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;					// VBO Name Generation Procedure
extern PFNGLBINDBUFFERARBPROC glBindBufferARB;					// VBO Bind Procedure
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;					// VBO Data Loading Procedure
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;	

bool IsExtensionSupported( char* TargetExtension ){
	const unsigned char *Extensions = NULL;
	const unsigned char *Start;
	unsigned char *Where, *Terminator;

	Where = (unsigned char *) strchr( TargetExtension, ' ' );	// Extension names should not have spaces
	if( Where || *TargetExtension == '\0' )
		return false;
	Extensions = glGetString( GL_EXTENSIONS );	              // Get Extensions String
	Start = Extensions;                                       // Search The Extensions String For An Exact Copy
	for(;;)
	{
		Where = (unsigned char *) strstr( (const char *) Start, TargetExtension );
		if( !Where )
			break;
		Terminator = Where + strlen( TargetExtension );
		if( Where == Start || *( Where - 1 ) == ' ' )
			if( *Terminator == ' ' || *Terminator == '\0' )
				return true;
		Start = Terminator;
	}
	return false;
}

void printOGLinfo(void){
  printf("openGL  = %s by %s\n", (char *) glGetString(GL_RENDERER), (char *) glGetString(GL_VENDOR));
  printf("version = %s\n", (char *) glGetString(GL_VERSION));
}

bool init_2Dopengl(const int window_w, const int window_h){
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );                   // CBlack background
  glViewport( 0, 0, window_w, window_h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(0.0f, window_w, window_h, 0.0f, -1.0f, 1.0f);
  glDisable (GL_DEPTH_TEST);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glColor4f(1.0f,1.0f,1.0f,0.5f);
  return true;
}

bool init_3Dopengl(const int window_w, const int window_h,const camera_type camera){
  GLfloat h = (GLfloat) window_h / (GLfloat) window_w;
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen And Depth Buffer
  glEnable(GL_NORMALIZE);
  glViewport(0, 0, (GLint) window_w, (GLint) window_h);
  glMatrixMode(GL_PROJECTION);						        // Select The Projection Matrix
	glLoadIdentity();									              // Reset The Projection Matrix
	glFrustum(-1.0, 1.0, -h, h, 1.0, 600.0);         // Frustrum setup (otherwise we need glut)
  glEnable (GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);							        // Select The Modelview Matrix
  //printf("Camera: %f %f %f\n",camera.x,camera.y,camera.z);
  //printf("Angles: %f %f\n",camera.angle_h,camera.angle_v);
	glLoadIdentity();									              // Reset The Modelview Matrix
  glRotatef(camera.angle_h,0.0f,1.0f,0.0f);
	glRotatef(camera.angle_v,1.0f,0.0f,0.0f);
	glTranslatef(camera.x,camera.y,camera.z);
  
  return true;
}

void rendertest_3ds(model_3ds model,const float x, const float y, const float z){
  if(!model.loaded){printf("model not loaded");return;}
  if(model.buffered){
    glEnableClientState(GL_VERTEX_ARRAY);                     // activate vertex coords array
    glEnableClientState(GL_COLOR_ARRAY);
   // glEnableClientState(GL_TEXTURE_COORD_ARRAY);				      // Disable Texture Coord Arrays
    
    glBindBufferARB( GL_ARRAY_BUFFER_ARB , model.VBOvertex);    // for vertex coordinates
    glVertexPointer( 3, GL_FLOAT, 0,0 );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB , model.VBOcolor);     // colors
    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, 0);
   // glBindBufferARB( GL_ARRAY_BUFFER_ARB , model.VBOmapcoord);  // mapping coordingates
   // glTexCoordPointer( 2, GL_FLOAT, 0, 0 );

    glPushMatrix();
      glTranslatef(x, y, z);
      glColor4f( 0.5f,  0.5f, 0.5f, 0.5f);
      glScalef(  0.1f,  0.1f, 0.1f);
      glRotatef( 90.0f,-1.0f, 0.0f, 0.0f);
      glDrawArrays( GL_TRIANGLES , 0 , 3*model.num_polygons);     //There are 3 times more vertices in memory
    glPopMatrix(); 
    

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    
    glDisableClientState( GL_VERTEX_ARRAY );				        // Disable Vertex Arrays
    glDisableClientState( GL_COLOR_ARRAY );                 //Disable Color arrays
   // glDisableClientState( GL_TEXTURE_COORD_ARRAY );				  // Disable Texture Coord Arrays
  }else{
    
  }

}

void render_scene(ApplicationInfo app,const int width, const int height){
  init_3Dopengl(width,height,app.camera);
  rendermap(app);
  rendertest_3ds(app.objects[0],0.0,0.0,-10.0);
  glFlush();
  init_2Dopengl(width,height);
  render_hud(width,height,app);
  SDL_GL_SwapBuffers();
}

