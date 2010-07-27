#include "TGALoader.h"

int findtexture(ApplicationInfo application,const char* name){
  for(int x = 0;x<application.num_textures;x++){
    //printf("%d %s\n",x,application.textures[x].name);
    if(strstr(application.textures[x].name,name)){
      return x;
    }
  }
  return -1;
}

bool printtextures(ApplicationInfo application){
  for(int x = 0;x<application.num_textures;x++){
    printf("Buffer:%d Name:%s\n",x,application.textures[x].name);
  } 
  return true;
}

bool initializefont(ApplicationInfo* application){
  application->font_texture = findtexture((*application),(const char*)"Font");
  if(application->font_texture != -1){
    if(fontfromtexture(application)){
      return true;
    }else{
      error_nonfatal("Building font display list failed","initializefont");
    }  
  }
  error_nonfatal("No font found in texture list","initializefont");
  return false;
}

int fontfromtexture(ApplicationInfo* application){
	GLuint base = glGenLists(256);									            // Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, application->textures[application->font_texture].texID);		        // Select Our Font Texture
	for (int loop1=0; loop1<256; loop1++){					            // Loop Through All 256 Lists
		float cx=float(loop1%16)/16.0f;						                // X Position Of Current Character
		float cy=float(loop1/16)/16.0f;						                // Y Position Of Current Character
		glNewList(base+loop1,GL_COMPILE_AND_EXECUTE);				      // Start Building A List
			glBegin(GL_QUADS);								                      // Use A Quad For Each Character
				glTexCoord2f(cx,1.0f-cy-0.0625f);			                // Texture Coord (Bottom Left)
				glVertex2d(0,16);							                        // Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	            // Texture Coord (Bottom Right)
				glVertex2i(16,16);							                      // Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);	            // Texture Coord (Top Right)
				glVertex2i(16,0);							                        // Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy-0.001f);			                // Texture Coord (Top Left)
				glVertex2i(0,0);							                        // Vertex Coord (Top Left)
			glEnd();										                            // Done Building Our Quad (Character)
			glTranslated(14,0,0);							                      // Move To The Right Of The Character
		glEndList();										                          // Done Building The Display List
	}						                                								// Loop Until All 256 Are Built
  printf("Font loaded from texture: %d\n",application->font_texture);
  application->textures[application->font_texture].base=base;
  return true;
}

bool clearDisplayList(ApplicationInfo application){	                                                // Delete The Font From Memory
	glDeleteLists(application.textures[application.font_texture].base,256);								            // Delete All 256 Display Lists
  free((void*)application.textures);
  return true;
}

void loadTextures(ApplicationInfo *application){
  application->num_textures=getnumfiles("data/Textures",".tga");
  application->textures = (TextureImage*)malloc(sizeof(TextureImage)*application->num_textures);
  for(int x=0;x< application->num_textures;x++){
    loadtgafromfile(application,x,getfilename("data/Textures",".tga",x));
  }
  initializefont(application);
}

bool loadtgafromfile(ApplicationInfo *application,const int number,const char *filename){	      // Loads A TGA File Into Memory
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	                              // Uncompressed TGA Header
	GLubyte		TGAcompare[12];								                                          // Used To Compare TGA Header
	GLubyte		header[6];									                                            // First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								                                          // Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									                                            // Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										                                                // Temporary Variable
	GLuint		type=GL_RGBA;								                                            // Set The Default GL Mode To RBGA (32 BPP)
  printf("Open tga-file: %s into texture %d\n",filename,number);
	FILE *file = fopen(filename, "rb");						                                    // Open The TGA File
	if(	file==NULL ||										                                              // Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	            // Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	                    // Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				                    // If So Read Next 6 Header Bytes
	{
		file == NULL ? : fclose(file);
		return false;	
	}
  
  application->textures[number].texID=number;
  application->textures[number].name=filename;
  application->textures[number].width  = header[1] * 256 + header[0];			          // Determine The TGA Width	(highbyte*256+lowbyte)
	application->textures[number].height = header[3] * 256 + header[2];			          // Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	application->textures[number].width	<=0	|| application->textures[number].height	<=0	|| (header[4]!=24 && header[4]!=32)){					// TGA 24 or 32 Bit?
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	application->textures[number].bpp	= header[4];							                                                    // Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	      = application->textures[number].bpp/8;						                                          // Divide By 8 To Get The Bytes Per Pixel
	imageSize		        = application->textures[number].width*application->textures[number].height*bytesPerPixel;	  // Calculate The Memory Required For The TGA Data
	GLubyte* imageData  = (GLubyte*)malloc(sizeof(GLubyte)*imageSize);		                                          // Reserve Memory To Hold The TGA Data

	if(	imageData==NULL || fread(imageData, 1, imageSize, file)!=imageSize){	// Does The Image Size Match The Memory Reserved?
		if(imageData!=NULL)						// Was Image Data Loaded
			free(imageData);						// If So, Release The Image Data
		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; int(i)<int(imageSize); i+=bytesPerPixel){		        // Loop Through The Image Data
		temp=imageData[i];							                                  // Temporarily Store The Value At Image Data 'i'
		imageData[i] = imageData[i + 2];	                                // Set The 1st Byte To The Value Of The 3rd Byte
		imageData[i + 2] = temp;					                                // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}
	fclose (file);											// Close The File and build A Texture From The Data
  application->textures[number].texID=number;
	glBindTexture(GL_TEXTURE_2D, application->textures[number].texID);			        // Bind Our Texture
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (application->textures[number].bpp==24){									// Was The TGA 24 Bits
		type=GL_RGB;										        // If So Set The 'type' To GL_RGB
	}
	glTexImage2D(GL_TEXTURE_2D, 0, type, application->textures[number].width, application->textures[number].height, 0, type, GL_UNSIGNED_BYTE, imageData);
  free(imageData);
	return true;											        // Texture Building Went Ok, Return True
}

