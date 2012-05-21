/**
 * \file GUI/entities/terrain.cpp
 * \brief Code file, Implementation of class: \ref terrain
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#include "terrain.h"

terrain::terrain(void){
  this->terrainGridWidth = 0;
  this->terrainGridLength= 0;
  this->terrainHeights   = NULL;
  this->terrainColors    = NULL;
  this->terrainNormals   = NULL;
  this->terrainLightPos  = new float[4];
  this->terrainDiffuseCol= new float[3];
  this->terrainAmbientCol= new float[3];
  this->terrainSimLight  = 1;
  this->iterationsDone   = 0;
  this->maxDisp          = 1.0;
  this->minDisp          = 0.1;
  this->itMinDisp        = 100;
  this->terrainWaveSize  = 3.0;
  this->terrainFunction  = MPD;
  this->terrainCircleSize= 100.0;
  this->terrainRandomSeed= 0;
  this->roughness        = 1.0;
  this->steps            = 1;
  this->terrainPMode     = ROLL;
  this->transX           = 0.0;
  this->transY           = 0.0;
  this->transZ           = 0.0;
  this->scaleX           = 1.0;
  this->scaleZ           = 1.0;
}

terrain::~terrain(void){

}


static float filterIdentity[25] = {
		0.0,0.0,0.0,0.0,0.0,
		0.0,0.0,0.0,0.0,0.0,
		0.0,0.0,1.0,0.0,0.0,
		0.0,0.0,0.0,0.0,0.0,
		0.0,0.0,0.0,0.0,0.0};

static float terrainFilter[25] = {
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	0.0,	1.0,	0.0,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0};

float terrain::getxlength() {
	return ( terrainGridWidth * scaleX);
}

float terrain::getylength() {
	return ( terrainGridLength * scaleZ);
}

void terrain::setlight(float x, float y, float z,float w) {

	terrainLightPos[0] = x;
	terrainLightPos[1] = y;
	terrainLightPos[2] = z;
	terrainLightPos[3] = w;

	/* normalise this vector to save time later */
	if (terrainLightPos[3] == 0.0) vectornormalize(terrainLightPos);
}

void terrain::setlightcolordiffuse(float r, float g, float b) {
	terrainDiffuseCol[0] = r ;
	terrainDiffuseCol[1] = g;
	terrainDiffuseCol[2] = b;
}

void terrain::setlightcolorambient(float r, float g, float b) {

	terrainAmbientCol[0] = r;
	terrainAmbientCol[1] = g;
	terrainAmbientCol[2] = b;
}



int terrain::SimulateLighting(int sim) {

	terrainSimLight = sim;

	if (sim) {
		/* just in case we don't have normals already */
		if (terrainNormals == NULL) {
			terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
			ComputeNormals();
		}
		if (terrainNormals == NULL) 
			return(TERRAIN_ERROR_MEMORY_PROBLEM);
		else
			return(TERRAIN_OK);
	}
	else
		return(TERRAIN_OK);

}


float *terrain::CrossProduct(int x1,int z1,int x2,int z2,int x3,int z3) {

	float *auxNormal,v1[3],v2[3];
		
	v1[0] = (x2-x1) * scaleX; 
	v1[1] = -terrainHeights[z1 * terrainGridWidth + x1] + terrainHeights[z2 * terrainGridWidth + x2];
	v1[2] = (z2-z1) * scaleZ; 


	v2[0] = (x3-x1) * scaleX; 
	v2[1] = -terrainHeights[z1 * terrainGridWidth + x1] + terrainHeights[z3 * terrainGridWidth + x3];
	v2[2] = (z3-z1) * scaleZ; 

	auxNormal = (float *)malloc(sizeof(float)*3);

	auxNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];
	auxNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
	auxNormal[1] = v1[2] * v2[0] - v1[0] * v2[2];

	return(auxNormal);
}

void terrain::AddVector(float *a, float *b) {

	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

void terrain::ComputeNormals(void) {

	float *norm1,*norm2,*norm3,*norm4; 
	int i,j,k;
	
	if (terrainNormals == NULL)
		return;


	for(i = 0; i < terrainGridLength; i++)
		for(j = 0; j < terrainGridWidth; j++) {
			norm1 = NULL;
			norm2 = NULL;
			norm3 = NULL;
			norm4 = NULL;

			/* normals for the four corners */
			if (i == 0 && j == 0) {
				norm1 = CrossProduct(0,0, 0,1, 1,0);	
				vectornormalize(norm1);				
			}
			else if (j == terrainGridWidth-1 && i == terrainGridLength-1) {
				norm1 = CrossProduct(j,i, j,i-1, j-1,i);	
				vectornormalize(norm1);				
			}
			else if (j == 0 && i == terrainGridLength-1) {
				norm1 = CrossProduct(j,i, j+1,i, j,i-1);	
				vectornormalize(norm1);				
			}
			else if (j == terrainGridWidth-1 && i == 0) {
				norm1 = CrossProduct(j,i, j-1,i, j,i+1);	
				vectornormalize(norm1);				
			}

			/* normals for the borders */
			else if (i == 0) {
				norm1 = CrossProduct(j,0, j-1,0, j,1);
				vectornormalize(norm1);
				norm2 = CrossProduct(j,0,j,1,j+1,0);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
			}
			else if (j == 0) {
				norm1 = CrossProduct(0,i, 1,i, 0,i-1);
				vectornormalize(norm1);
				norm2 = CrossProduct(0,i, 0,i+1, 1,i);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
			}
			else if (i == terrainGridLength-1) {
				norm1 = CrossProduct(j,i, j+1,i, j,i-1);
				vectornormalize(norm1);
				norm2 = CrossProduct(j,i, j,i-1, j-1,i);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
			}
			else if (j == terrainGridWidth-1) {
				norm1 = CrossProduct(j,i, j,i-1, j-1,i);
				vectornormalize(norm1);
				norm2 = CrossProduct(j,i, j-1,i, j,i+1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
			}

			/* normals for the inner vertices using 8 neighbours */
			else {
				norm1 = CrossProduct(j,i, j-1,i, j-1,i+1);
				vectornormalize(norm1);
				norm2 = CrossProduct(j,i, j-1,i+1, j,i+1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j,i+1, j+1,i+1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j+1,i+1, j+1,i);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j+1,i, j+1,i-1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j+1,i-1, j,i-1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j,i-1, j-1,i-1);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
				norm2 = CrossProduct(j,i, j-1,i-1, j-1,i);
				vectornormalize(norm2);
				AddVector(norm1,norm2);
				free(norm2);
			}

			vectornormalize(norm1);
			norm1[2] = - norm1[2];
			for (k = 0; k< 3; k++) 
				terrainNormals[3*(i*terrainGridWidth + j) + k] = norm1[k];

			free(norm1);

		}
}


int terrain::LoadFromImage(const char *filename, int normals) {
  message("[TERRAIN]\tLoading terrain from: %s",filename);
	tgaInfo *info;
	int mode;
	float pointHeight;

  /* if a terrain already exists, destroy it. */
	if (terrainHeights != NULL) Destroy();
		
  /* load the image, using the tgalib */
	info = tgaLoad(filename);

	if (info->status != TGA_OK)	return(TERRAIN_ERROR_LOADING_IMAGE);

  /* if the image is RGB, convert it to greyscale mode will store the image's number of components */
	mode = info->pixelDepth / 8;
	if (mode == 3) {
		tgaRGBtoGreyscale(info);
		mode = 1;
	}
	
  /* set the width and height of the terrain */
	terrainGridWidth = info->width;
	terrainGridLength = info->height;

  /* alocate memory for the terrain, and check for errors */
	terrainHeights = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float));
	if (terrainHeights == NULL) return(TERRAIN_ERROR_MEMORY_PROBLEM);

/* allocate memory for the normals, and check for errors */
	if (normals) {
		terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
		if (terrainNormals == NULL)	return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}else{
    terrainNormals = NULL;
  }

/* if mode = RGBA then allocate memory for colors, and check for errors */
	if (mode == 4) {
		terrainColors = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float)*3);
		if (terrainColors == NULL) return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}else{
		terrainColors = NULL;
  }

/* fill arrays */
	for (int i = 0 ; i < terrainGridLength; i++)
		for (int j = 0;j < terrainGridWidth; j++) {

/* compute the height as a value between 0.0 and 1.0 */
			pointHeight = info->imageData[mode*(i*terrainGridWidth + j)+(mode-1)] / 255.0;
			terrainHeights[i*terrainGridWidth + j] = pointHeight;
/* if mode = RGBA then fill the colors array as well */
			if (mode==4) {
				terrainColors[3*(i*terrainGridWidth + j)]   = (info->imageData[mode*(i*terrainGridWidth + j)])/255.0;
				terrainColors[3*(i*terrainGridWidth + j)+1] = (info->imageData[mode*(i*terrainGridWidth + j)+1])/255.0;
				terrainColors[3*(i*terrainGridWidth + j)+2] = (info->imageData[mode*(i*terrainGridWidth + j)+2])/255.0;
			}
		}
/* if we want normals then compute them		*/
	if (normals){
		ComputeNormals();
    message("[TERRAIN]\tComputed normals");  
  }
/* free the image's memory  */
	tgaDestroy(info);
	
	return(TERRAIN_OK); 
}

int terrain::ScaleHeights(float min,float max) {
	float amp,aux,min1,max1,height;
	int total,i;

	if (terrainHeights == NULL)
		return(TERRAIN_ERROR_NOT_INITIALISED);

	if (min > max) {
		aux = min;
		min = max;
		max = aux;
	}

	amp = max - min;
	total = terrainGridWidth * terrainGridLength;

	min1 = terrainHeights[0];
	max1 = terrainHeights[0];
	for(i=1;i < total ; i++) {
		if (terrainHeights[i] > max1)
			max1 = terrainHeights[i];
		if (terrainHeights[i] < min1)
			min1 = terrainHeights[i];
	}
	if (min1 != max1) {
		for(i=0;i < total;i++) {
		height = (terrainHeights[i] - min1) / (max1-min1);
		terrainHeights[i] = height * amp + min;
		}
		if (terrainNormals != NULL)
			ComputeNormals();
	}
	return(TERRAIN_OK);
}

float terrain::ComputeLightFactor(int i,int j,int offseti, int offsetj) {
	float factor,v[3];

	if (terrainNormals != NULL) {
		if (terrainLightPos[3] == 0.0) /* directional light */
		factor = terrainNormals[3*(i * terrainGridWidth + j)] * terrainLightPos[0] + terrainNormals[3*(i * terrainGridWidth + j) +1] * terrainLightPos[1] +	terrainNormals[3*(i * terrainGridWidth + j) +2] * terrainLightPos[2];
		else { /* positional light */
			v[0] = terrainLightPos[0] - ((j + offsetj) + transX) * scaleX;
			v[1] = terrainLightPos[1] - terrainHeights[i*terrainGridWidth + j] + transY;
			v[2] = terrainLightPos[2] - ((offseti -i)  + transZ) * scaleZ;
			vectornormalize(v);
			factor = terrainNormals[3*(i * terrainGridWidth + j)] * v[0] + terrainNormals[3*(i * terrainGridWidth + j) +1] * v[1] +	terrainNormals[3*(i * terrainGridWidth + j) +2] * v[2];
		}
		if (factor < 0)	factor = 0;
	}
	else
		factor = 1;
	
	return(factor);
}


void terrain::render(void){
  if(this->buffered){
    glCallList(this->displaylist);
  }else{

  }
}

void terrain::setGLcolor(int x, int z){
  int startW = terrainGridWidth / 2 - terrainGridWidth;
	int startL = - terrainGridLength / 2 + terrainGridLength;
	float factor;
  if (!(x > terrainGridWidth) || !(z > terrainGridLength) || !(x < 0) || !(z < 0)){;
    if (terrainSimLight  && terrainColors != NULL){
      factor = ComputeLightFactor(z,x,startL,startW);
      glColor3f(terrainColors[3*((z)*terrainGridWidth + x)] * factor + terrainAmbientCol[0], 
                terrainColors[3*((z)*terrainGridWidth + x)+1] * factor + terrainAmbientCol[1], 
                terrainColors[3*((z)*terrainGridWidth + x)+2] * factor + terrainAmbientCol[2]);
    }else if (terrainSimLight  && terrainColors == NULL){
      factor = ComputeLightFactor(z+1,x,startL,startW);
      glColor3f(terrainDiffuseCol[0] * factor + terrainAmbientCol[0],
                terrainDiffuseCol[1] * factor + terrainAmbientCol[1],
                terrainDiffuseCol[2] * factor + terrainAmbientCol[2]);
    }else if (terrainColors != NULL){    
      glColor3f(terrainColors[3*((z)*terrainGridWidth + x)], 
                terrainColors[3*((z)*terrainGridWidth + x)+1], 
                terrainColors[3*((z)*terrainGridWidth + x)+2]);
    }
  }
}

int terrain::buffer(int lighting,int faceType) {
  //message("[Terrain]\tCreating Calllist for heightmap");
  //message("[Terrain]\tDimensions: %d %d",terrainGridWidth,terrainGridLength);
	int i,j;
	int startW = terrainGridWidth / 2 - terrainGridWidth;
	int startL = - terrainGridLength / 2 + terrainGridLength;

  if(this->displaylist)glDeleteLists(this->displaylist,1);
	this->displaylist = glGenLists(1);
	if (lighting)	terrainSimLight = 1;
	glNewList(this->displaylist,GL_COMPILE);
	for (i = 0 ; i < terrainGridLength-1; i++) {
		glBegin(faceType);
		for(j=0; j < terrainGridWidth; j++) {
      setGLcolor(i,j);
			if (terrainNormals != NULL){
				glNormal3f(terrainNormals[3*((i+1)*terrainGridWidth + j)],
                   terrainNormals[3*((i+1)*terrainGridWidth + j)+1],
                   terrainNormals[3*((i+1)*terrainGridWidth + j)+2]);	
      }
      glVertex3f(((startW + j) + transX) * scaleX,terrainHeights[(i+1)*terrainGridWidth + (j)] + transY,((startL - (i+1)) + transZ) * scaleZ);
      setGLcolor(i,j);
			if (terrainNormals != NULL){
				glNormal3f(terrainNormals[3*(i*terrainGridWidth + j)],
                   terrainNormals[3*(i*terrainGridWidth + j)+1],
                   terrainNormals[3*(i*terrainGridWidth + j)+2]);
      }
      glVertex3f(((startW + j) + transX) * scaleX, terrainHeights[i*terrainGridWidth + j] + transY, ((startL - i) + transZ) * scaleZ);
		}
		glEnd();
	}
	glEndList();
  this->buffered=true;
	return(this->displaylist);
}


float terrain::getheight(int x, int z) {
	int xt,zt;

	if (terrainHeights == NULL) return(0.0);

	xt = x + terrainGridWidth /2;
	zt = terrainGridLength - (z + terrainGridLength /2);
	if ((x > terrainGridWidth) || (z > terrainGridLength) || (x < 0) || (z < 0)) return(0.0);

	return(terrainHeights[z * terrainGridWidth + x]);
}

/*
float terrain::Height(int x,int z) {
	if (x > terrainGridWidth-1)
		x -= (terrainGridWidth-1);
	else if (x < 0)
		x += terrainGridWidth-1;
	if (z > terrainGridLength-1)
		z -= (terrainGridLength-1);
	else if (z < 0)	
		z += terrainGridLength-1;
	assert(x>=0 && x < terrainGridWidth);
	assert(z>=0 && z < terrainGridLength);
	return(terrainHeights[x * terrainGridWidth + z]);
}
*/

void terrain::Destroy() {
	if (terrainHeights != NULL) {
		free(terrainHeights);
		terrainHeights = NULL;
	}

	if (terrainColors != NULL) {
		free(terrainColors);
		terrainColors = NULL;
	}

	if (terrainNormals != NULL) {
		free(terrainNormals);
		terrainNormals = NULL;
	}
}

void terrain::SetNormals(int normals) {
	if (normals) {
		terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float)*3);
		ComputeNormals();
	}else if (terrainNormals != NULL){
		free(terrainNormals);
		terrainNormals = NULL;
	}
}

void terrain::SetOrigin(float x,float y,float z) {
	transX = x;
	transY = y;
	transZ = z;
}

void terrain::setscale(float x, float z) {
	scaleX = x;
	scaleZ = z;
}

void terrain::Init(int x, int y) {
	int i;

	terrainGridWidth = x;
	terrainGridLength = y;

	if (terrainHeights != NULL)
		Destroy();

	terrainHeights = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float));
	terrainColors = NULL;
	terrainNormals = NULL;

	for (i=0;i<terrainGridWidth*terrainGridLength; i++)
		terrainHeights[i] = 0.0;
	iterationsDone = 0;
}

void terrain::SetRandomSeed(int rs) {
	terrainRandomSeed = rs;
	srand(rs);
}

void terrain::SetMaxDisp(float maxdisp1) {
	maxDisp = maxdisp1;
}

void terrain::SetMinDisp(float mindisp1) {
	minDisp = mindisp1;
}

void terrain::SetItMinDisp(int it) {
	itMinDisp = it;
}

void terrain::SetWaveSize(float ws) {
	terrainWaveSize = ws;
}

void terrain::SetCircleSize(float cs) {
	terrainCircleSize = cs*cs;
}

void terrain::SetFunction(int fun) {
	terrainFunction = fun;
}

void terrain::SetRoughness(float r) {
	roughness = 1.0/r;
}


int terrain::Iterate(int numIt) {
	if ((iterationsDone == 0) || (terrainFunction == MPD)) {
		srand(terrainRandomSeed);
	}

	if (terrainFunction == CIRCLE) return(IterateCircles(numIt));
	else if (terrainFunction == MPD) return(IterateMidPointDisplacement(numIt,maxDisp,roughness));
	else if (terrainFunction == RandomDirection) return(IterateParticleDeposition(numIt));
	else return(IterateFault(numIt));
}

int terrain::IterateFault(int numIterations) {
	float dispAux,pd;
	int i,j,k,halfX,halfZ;
	float a,b,c,w,d;

	if (terrainHeights == NULL)	return(TERRAIN_ERROR_NOT_INITIALISED);

	halfX = terrainGridWidth / 2;
	halfZ = terrainGridLength / 2;
	for (k = 0; k < numIterations;k++) {
		d = sqrt(halfX * halfX + halfZ * halfZ);
		w = rand();
		a = cos(w);
		b = sin(w);
		c = ((float)rand() / RAND_MAX) * 2*d  - d; 
		
		iterationsDone++;
		if (iterationsDone < itMinDisp)
			disp = maxDisp + (iterationsDone/(itMinDisp+0.0))* (minDisp - maxDisp);
		else
			disp = minDisp;
		for (i = 0;i < terrainGridLength; i++)
			for(j = 0; j < terrainGridWidth; j++) {
				switch(terrainFunction){
				case STEP:
					if ((i-halfZ) * a + (j-halfX) * b + c > 0)
						dispAux = disp;
					else
						dispAux = -disp;
					break;
				case SIN:
					pd = ((i-halfZ) * a + (j-halfX) * b + c)/terrainWaveSize;
					if (pd > 1.57) pd = 1.57;
					else if (pd < 0) pd = 0;
					dispAux = -disp/2 + sin(pd)*disp;
					break;
				case COS:
					pd = ((i-halfZ) * a + (j-halfX) * b + c)/terrainWaveSize;
					if (pd > 3.14) pd = 3.14;
					else if (pd < -3.14) pd = -3.14;
					dispAux =  disp-(terrainWaveSize/(terrainGridWidth+0.0)) + cos(pd)*disp;
					break;
				}
				terrainHeights[i*terrainGridWidth + j] += dispAux;
			}
	}
	if (terrainNormals != NULL)	ComputeNormals();
	return(TERRAIN_OK);
}

int terrain::IterateCircles(int numIterations) {
	float dispAux;
	int i,j,k,halfX,halfZ,dispSign;
	float x,z,r,pd;

	if (terrainHeights == NULL)	return(TERRAIN_ERROR_NOT_INITIALISED);

	halfX = terrainGridWidth / 2;
	halfZ = terrainGridLength / 2;
	for (k = 0; k < numIterations;k++) {

		z = ((float)rand() / RAND_MAX) * terrainGridWidth;
		x = ((float)rand() / RAND_MAX) * terrainGridLength;
		iterationsDone++;
		if (iterationsDone < itMinDisp)
			disp = maxDisp + (iterationsDone/(itMinDisp+0.0))* (minDisp - maxDisp);
		else
			disp = minDisp;
		r = ((float)rand() / RAND_MAX);
		if (r > 0.5)
			dispSign = 1;
		else
			dispSign = -1;
		for (i = 0;i < terrainGridLength; i++)
			for(j = 0; j < terrainGridWidth; j++) {
					pd = sqrt(((i-x)*(i-x) + (j-z)*(j-z)) / terrainCircleSize)*2;
					if (pd > 1) dispAux = 0.0;
					else if (pd < -1) dispAux = 0.0;
					else
						dispAux =  disp/2*dispSign + cos(pd*3.14)*disp/2 * dispSign;
				
				terrainHeights[i*terrainGridWidth + j] += dispAux;
			}
	}
	if (terrainNormals != NULL)	ComputeNormals();
	return(TERRAIN_OK);
}



static float terrainRandom(float dispH) {
	float r;

	r = ( ( (float)rand() ) / ( (float)RAND_MAX ) ) * dispH - (dispH * 0.5);
	return(r);
}

void terrain::MPDDiamondStep(int i,int j,int step,float dispH) {
	terrainHeights[(i+step/2)*terrainGridWidth + j+step/2] = 
					(getheight(i,j) + 
					getheight(i+step,j) + 
					getheight(i+step,j+step) + 
					getheight(i,j+step)) / 4;
	terrainHeights[(i+step/2)*terrainGridWidth + j+step/2] += terrainRandom(dispH);
}

/*
void terrainMPDSquareStep(int x1,int z1, int step, float dispH) {

	int i,j;
	float x,z;

	x = x1 + step/2;
	z = z1 + step/2;

	i = x + step/2;
	j = z;
	terrainHeights[i*terrainGridWidth + j] = 
					(terrainHeight(i,j+step/2) + 
					terrainHeight(i,j-step/2) + 
					terrainHeight(i-step/2,j) + 
					terrainHeight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);

	j = z + step/2;
	i = x;
	terrainHeights[i*terrainGridWidth + j] = 
					(terrainHeight(i,j+step/2) + 
					terrainHeight(i,j-step/2) + 
					terrainHeight(i-step/2,j) + 
					terrainHeight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
	
	i = x - step/2;
	j = z;
if (i == 0){
	terrainHeights[i*terrainGridWidth + j] = 
					(terrainHeight(i,j+step/2) + 
					terrainHeight(i,j-step/2) + 
					terrainHeight(i-step/2,j) + 
					terrainHeight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
}
	j = z - step/2;
	i = x;
if (j == 0){
	terrainHeights[i*terrainGridWidth + j] = 
					(terrainHeight(i,j+step/2) + 
					terrainHeight(i,j-step/2) + 
					terrainHeight(i-step/2,j) + 
					terrainHeight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
}
}
*/

void terrain::MPDSquareStep(int x1,int z1, int step, float dispH) {
	int i,j;
	int x,z;

	x = x1 + step/2;
	z = z1 + step/2;

	i = x + step/2;
	j = z;
	if (i == terrainGridLength-1)
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j+step/2) + 
						getheight(i,j-step/2) + 
						getheight(i-step/2,j)) / 3;
	else
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j+step/2) + 
						getheight(i,j-step/2) + 
						getheight(i-step/2,j) + 
						getheight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);

	j = z + step/2;
	i = x;
	if (j == terrainGridWidth-1)
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j-step/2) + 
						getheight(i-step/2,j) + 
						getheight(i+step/2,j)) / 3;
	else
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j+step/2) + 
						getheight(i,j-step/2) + 
						getheight(i-step/2,j) + 
						getheight(i+step/2,j)) / 4;
	terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
	
	i = x - step/2;
	j = z;
	if (i == 0){
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j+step/2) + 
						getheight(i,j-step/2) + 
						getheight(i+step/2,j)) / 3;
		terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
	}

	j = z - step/2;
	i = x;
	if (j == 0){
		terrainHeights[i*terrainGridWidth + j] = 
						(getheight(i,j+step/2) + 
						getheight(i-step/2,j) + 
						getheight(i+step/2,j)) / 3;
		terrainHeights[i*terrainGridWidth + j] += terrainRandom(dispH);
	}
}


int terrain::IterateMidPointDisplacement(int steps,float maxDispH,float r) {
	int i,j,step;
	float m = maxDispH;

	terrainGridWidth = (int)powerint(2,steps) + 1;
	terrainGridLength = terrainGridWidth;
	Init(terrainGridWidth,terrainGridWidth);
	
	for (step = terrainGridWidth-1; step > 1; step /= 2 ) {

		for (i = 0;i<terrainGridLength-2;i+=step)
			for(j=0;j<terrainGridWidth-2;j+=step) {
				MPDDiamondStep(i,j,step,m);
				
			}

		for (i = 0;i<terrainGridLength-2;i+=step)
			for(j=0;j<terrainGridWidth-2;j+=step) {
				MPDSquareStep(i,j,step,m);
				
			}
		m *= pow(2,-r);
	}
	return(TERRAIN_OK);
}

void terrain::ResetFilter() {
	memcpy(terrainFilter, filterIdentity,filterSize);
}

void terrain::SetFilter(float *newFilter) {
	memcpy(terrainFilter, newFilter,filterSize);
}

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

int terrain::ApplyFilter() {

	int i,j,k1,k2,h1,h2,k,h;
	float aux,*terrainAux,filterSum;;

	terrainAux = (float *)malloc(sizeof(float)* terrainGridWidth * terrainGridLength);
	if (terrainAux == NULL)	return TERRAIN_ERROR_MEMORY_PROBLEM;

	for(i=0;i < terrainGridLength;i++)
		for(j=0;j < terrainGridWidth; j++) {
			aux = 0.0;
			filterSum = 0.0;
			k1 = max(0,i-2);
			k2 = min(i+3, terrainGridLength);
			for (k = k1; k < k2; k++) {
				h1 = max(0,j-2);
				h2 = min(j+3, terrainGridWidth);
				for (h = h1;h < h2; h++) {
					aux += (terrainHeights[(k)*terrainGridWidth + (h)] * 
						   terrainFilter[(k-i+2)*5 + (h-j+2)]);
					filterSum += terrainFilter[(k-i+2)*5 + (h-j+2)];
				}
			}
			terrainAux[i*terrainGridWidth + j] = aux / filterSum;
		}

	memcpy(terrainHeights,terrainAux,sizeof(float)* terrainGridWidth * terrainGridLength);

	free(terrainAux);

	if (terrainNormals != NULL)	ComputeNormals();
	return(TERRAIN_OK);
}

void terrain::Smooth(float k) {
	int i,j;

	for(i=0;i<terrainGridLength;i++)
		for(j=1;j<terrainGridWidth;j++)
			terrainHeights[i*terrainGridWidth + j] =
				terrainHeights[i*terrainGridWidth + j] * (1-k) + 
				terrainHeights[i*terrainGridWidth + j-1] * k;
	for(i=1;i<terrainGridLength;i++)
		for(j=0;j<terrainGridWidth;j++)
			terrainHeights[i*terrainGridWidth + j] =
				terrainHeights[i*terrainGridWidth + j] * (1-k) + 
				terrainHeights[(i-1)*terrainGridWidth + j] * k;
	
	for(i=0; i<terrainGridLength; i++)
		for(j=terrainGridWidth-1;j>-1;j--)
			terrainHeights[i*terrainGridWidth + j] =
				terrainHeights[i*terrainGridWidth + j] * (1-k) + 
				terrainHeights[i*terrainGridWidth + j+1] * k;
	for(i=terrainGridLength-2;i<-1;i--)
		for(j=0;j<terrainGridWidth;j++)
			terrainHeights[i*terrainGridWidth + j] =
				terrainHeights[i*terrainGridWidth + j] * (1-k) + 
				terrainHeights[(i+1)*terrainGridWidth + j] * k;

	if (terrainNormals != NULL)	ComputeNormals();
}


void terrain::SetParticleMode(int mode) {
	terrainPMode = mode;
}


void terrain::deposit(int x, int z) {
	int j,k,kk,jj,flag;
	flag = 0;

	for (k=-1;k<2;k++){
		for(j=-1;j<2;j++){
			if (k!=0 && j!=0 && x+k>-1 && x+k<terrainGridWidth && z+j>-1 && z+j<terrainGridLength){
				if (terrainHeights[(x+k) * terrainGridLength + (z+j)] < terrainHeights[x * terrainGridLength + z]) {
					flag = 1;
					kk = k;
					jj = j;
				}
      }
    }
  }
	if (!flag) terrainHeights[x * terrainGridLength + z] += maxDisp;
	else deposit(x+kk,z+jj);
}


int terrain::IterateParticleDeposition(int numIt) {
		int x,z,i,dir;

	if (terrainHeights == NULL)
		return TERRAIN_ERROR_NOT_INITIALISED;

	x = rand() % terrainGridWidth;
	z = rand() % terrainGridLength;

	for (i=0; i < numIt; i++) {

		iterationsDone++;
		dir = rand() % 4;

		if (dir == 2) {
			x++;
			if (x >= terrainGridWidth)
				x = 0;
		}
		else if (dir == 3){
			x--;
			if (x == -1)
				x = terrainGridWidth-1;
		}
		
		else if (dir == 1) {
			z++;
			if (z >= terrainGridLength)
				z = 0;
		}
		else if (dir == 0){
			z--;
			if (z == -1)
				z = terrainGridLength - 1;
		}

		if (terrainPMode == ROLL)
			deposit(x,z);
		else
			terrainHeights[x * terrainGridLength + z] += maxDisp;
	}
	return(TERRAIN_OK);
}



int terrain::SaveAsTGA(char *filename) {
	unsigned char *imageData,point;
	int totalPoints,status,mode,i;
	float min,max;

	if (terrainHeights == NULL)	return TERRAIN_ERROR_NOT_INITIALISED;

	if (terrainColors == NULL)
		mode = 1;
	else 
		mode = 4;

	totalPoints = terrainGridWidth * terrainGridLength;
	min = terrainHeights[0];
	max = terrainHeights[0];
	for(i=1;i < totalPoints ; i++) {
		if (terrainHeights[i] > max)
			max = terrainHeights[i];
		if (terrainHeights[i] < min)
			min = terrainHeights[i];
	}

	imageData = (unsigned char *)malloc(sizeof(unsigned char) * totalPoints*mode);

	for(i=0;i < totalPoints; i++) {
		if (mode > 1) {
			imageData[i*mode] = (unsigned char)(terrainColors[i*(mode-1)])*256;
			imageData[i*mode+1] = (unsigned char)(terrainColors[i*(mode-1)+1])*256;
			imageData[i*mode+2]   = (unsigned char)(terrainColors[i*(mode-1)+2])*256;
		}
		point = (unsigned char)((terrainHeights[i] - min) / (max-min) * 255.0);
		imageData[i*mode + mode-1] = point;
	}
	status = tgaSaveSeries(filename,terrainGridWidth,terrainGridLength, mode*8, imageData);

	if(status==TGA_OK) return(TERRAIN_OK);
	else return(TERRAIN_ERROR_NOT_SAVED);
}
