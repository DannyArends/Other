#include "MAPLoader.h"


void setMap(ApplicationInfo* application,const char* name){
  for(int x = 0;x<application->num_maps;x++){
    if(strstr(application->maps[x].name,name)){
      application->c_map=x;
      printf("Starting on map %d\n",application->c_map);
      return;
    }
  }
}

bool loadmapfromfile(ApplicationInfo *application,const int number,char *filename){	
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	                              // Uncompressed TGA Header
	GLubyte		TGAcompare[12];								                                          // Used To Compare TGA Header
	GLubyte		header[6];									                                            // First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								                                          // Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									                                            // Used To Store The Image Size When Setting Aside Ram
	float     pointHeight;

  printf("Open map-file: %s into map %d\n",filename,number);
	FILE *file = fopen(filename, "rb");						                                    // Open The TGA File
	if(	file==NULL ||										                                              // Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	            // Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	                    // Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				                    // If So Read Next 6 Header Bytes
	{
		file == NULL ? : fclose(file);
		return false;	
	}
  
  application->maps[number].name=filename;
  application->maps[number].width  = header[1] * 256 + header[0];			          // Determine The TGA Width	(highbyte*256+lowbyte)
	application->maps[number].height = header[3] * 256 + header[2];			          // Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	application->maps[number].width	<=0	|| application->maps[number].height	<=0	|| (header[4]!=24 && header[4]!=32)){					// TGA 24 or 32 Bit?
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	application->maps[number].bpp	= header[4];							                                                    // Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	      = application->maps[number].bpp/8;						                                          // Divide By 8 To Get The Bytes Per Pixel
	imageSize		        = application->maps[number].width*application->maps[number].height*bytesPerPixel;	  // Calculate The Memory Required For The TGA Data
	GLubyte* imageData  = (GLubyte*)malloc(sizeof(GLubyte)*imageSize);		                                          // Reserve Memory To Hold The TGA Data
  int mode = bytesPerPixel;
	if(	imageData==NULL || fread(imageData, 1, imageSize, file)!=imageSize){	// Does The Image Size Match The Memory Reserved?
		if(imageData!=NULL)						// Was Image Data Loaded
			free(imageData);						// If So, Release The Image Data
		fclose(file);										// Close The File
		return false;										// Return False
	}

  application->maps[number].mapData = imageData;
	fclose (file);											// Close The File and build A Texture From The Data
  printf("Image data loaded for %s\n",filename);  
  float *terrainHeights = NULL;
  float *terrainColors = NULL;
  float *terrainNormals = NULL;  
  terrainHeights = (float *)malloc(application->maps[number].width * application->maps[number].height * sizeof(float));
	if (terrainHeights == NULL) return false;
	terrainNormals = (float *)malloc(application->maps[number].width * application->maps[number].height * sizeof(float) * 3);
	if (terrainNormals == NULL)	return false;
	terrainColors = (float *)malloc(application->maps[number].width * application->maps[number].height * sizeof(float)*3);
  if(terrainColors==NULL) return false;
 	for (unsigned int i = 0 ; i < application->maps[number].height; i++){
		for (unsigned int j = 0 ; j < application->maps[number].width; j++){
			pointHeight = application->maps[number].mapData[mode*(i*application->maps[number].width + j)+(mode-1)] / 25.5;      //Height 0-10
			terrainHeights[i*application->maps[number].width + j] = pointHeight;
			terrainColors[3*(i*application->maps[number].width + j)]   = (application->maps[number].mapData[mode*(i*application->maps[number].width + j)])/255.0;
			terrainColors[3*(i*application->maps[number].width + j)+1] = (application->maps[number].mapData[mode*(i*application->maps[number].width + j)+1])/255.0;
			terrainColors[3*(i*application->maps[number].width + j)+2] = (application->maps[number].mapData[mode*(i*application->maps[number].width + j)+2])/255.0;
		}
  }
  int startW,startL;
  float transX = 0.0f; 
  float transY = -10.0f;
  float transZ = 0.0f;
  float scaleX = 1.0f;
  float scaleZ = 1.0f;
  
  startW = (int) application->maps[number].width / 2 - application->maps[number].width;
	startL = (int)- application->maps[number].height / 2 + application->maps[number].height;
  
	application->maps[number].DisplayList = glGenLists(1);
	glNewList(application->maps[number].DisplayList,GL_COMPILE);
  printf("Compiling map %s in Displaylist %d\n",filename,application->maps[number].DisplayList);
	for (int i = 0 ; i < application->maps[number].height-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j < application->maps[number].width; j++) {
      glColor3f(terrainColors[3*((i+1)*application->maps[number].width + j)+2],
						  terrainColors[3*((i+1)*application->maps[number].width + j)+1],
						  terrainColors[3*((i+1)*application->maps[number].width + j)]);
			glVertex3f(
				((startW + j) + transX) * scaleX,
				terrainHeights[(i+1)*application->maps[number].width + (j)] + transY,
				((startL - (i+1)) + transZ) * scaleZ);
			glVertex3f(
				((startW + j) + transX) * scaleX,
				terrainHeights[i*application->maps[number].width + j] + transY,
				((startL - i) + transZ) * scaleZ);
		}
		glEnd();
	}
	glEndList();
  printf("Displaylist created\n");
  free(imageData);
  free(terrainHeights);
  free(terrainColors);
  return true;
}
  
void loadMaps(ApplicationInfo *application){
  application->num_maps=getnumfiles("data/Maps",".tga");
  application->maps = (map_type*)malloc(sizeof(map_type)*application->num_maps);
  for(int x=0;x< application->num_maps;x++){
    loadmapfromfile(application,x,getfilename("data/Maps",".tga",x));
  }
  setMap(application,(const char*)"Empty");
}
