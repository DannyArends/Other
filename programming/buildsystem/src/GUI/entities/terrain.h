/**
 * \file GUI/entities/terrain.h
 * \brief Header file, for GUI/entities/terrain.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

 #ifndef TERRAIN_H_
  #define TERRAIN_H_
  #include "ENTITIES.h"
  
  #define ROLL	0
  #define STICK	1
  #define filterSize 25*sizeof(float)
  
  enum TerrainType{ TERRAIN_ERROR_INVALID_PARAM = -5,TERRAIN_ERROR_LOADING_IMAGE = -4, TERRAIN_ERROR_MEMORY_PROBLEM = -3, TERRAIN_ERROR_NOT_SAVED = -2, TERRAIN_ERROR_NOT_INITIALISED = -1, TERRAIN_OK = 0};
  enum OptionsType{ STEP = 1, SIN = 2, COS=3, CIRCLE = 4, MPD = 5, RandomDirection = 6};
  
  /** 
      * \brief Three dimensional colored terrain from tga image (r,g,b,height)
      */
  class terrain:public entity{
  public:
    terrain(void);
    int   LoadFromImage(const char *filename, int normals);
    int   SaveAsTGA(char *filename);
    float getxlength();
    float getylength();
    float getheight(int x, int z);
    int   buffer(int lighting,int faceType);
    void  render(void);
    int   ScaleHeights(float min,float max);
    void  setGLcolor(int x, int z);
    int   SimulateLighting(int sim);
    void  setlight(float x, float y, float z,float w);
    void  setlightcolordiffuse(float r, float g, float b);
    void  setlightcolorambient(float r, float g, float b);
    void  SetNormals(int normals);
    void  SetOrigin(float x,float y,float z);
    void  setscale(float x, float z);
    void  Smooth(float k);
    void  ResetFilter();
    void  SetFilter(float *newFilter);
    int   ApplyFilter();

   ~terrain(void);
  private:
    void   Init(int x, int y);  
    int    IterateFault(int numIterations);
    void   SetRandomSeed(int rs);
    void   SetMaxDisp(float maxdisp1);
    void   SetMinDisp(float mindisp1);
    void   SetWaveSize(float ws);
    void   SetItMinDisp(int it);
    void   SetFunction(int fun);
    void   SetCircleSize(float cs);
    int    IterateCircles(int numIterations);
    int    Iterate(int numIt);
    int    IterateMidPointDisplacement(int steps,float maxDispH,float roughness);
    void   SetRoughness(float r);
    void   SetParticleMode(int mode);
    int    IterateParticleDeposition(int numIt);    
    void   Destroy();  
    float* CrossProduct(int x1,int z1,int x2,int z2,int x3,int z3);
    void   AddVector(float *a, float *b);
    void   ComputeNormals(void);
    float  ComputeLightFactor(int i,int j,int offseti, int offsetj);
    void   MPDDiamondStep(int i,int j,int step,float dispH);
    void   MPDSquareStep(int x1,int z1, int step, float dispH);
    void   deposit(int x, int z);
    
    int    terrainGridWidth,terrainGridLength;
    float* terrainHeights;
    float* terrainColors;
    float* terrainNormals;
    float* terrainLightPos;
    float* terrainDiffuseCol;
    float* terrainAmbientCol;
    int    terrainSimLight;
    int    iterationsDone;
    float  maxDisp,minDisp,disp;
    int    itMinDisp;
    float  terrainWaveSize,terrainCircleSize,roughness;
    int    terrainFunction,terrainRandomSeed,steps;
    int    terrainPMode;
    float  transX,transY,transZ,scaleX,scaleZ;
    float   cx,cy,cz;
    float   rad;
    uint    p;
    GLuint  displaylist;
    bool    buffered;
    float   twopi,pidtwo;    
  };

#endif
