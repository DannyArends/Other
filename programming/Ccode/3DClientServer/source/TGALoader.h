#ifndef __TGALOADER_H__
#define __TGALOADER_H__
#include "includes.h"
#include "DataStructures.h"
#include "Error.h"
#include "FileIO.h"

bool loadtgafromfile(ApplicationInfo* application,const int number,const char *filename);
void loadTextures(ApplicationInfo* application);
int findtexture(ApplicationInfo application,const char* name);
bool printtextures(ApplicationInfo application);
bool initializefont(ApplicationInfo* application);
int fontfromtexture(ApplicationInfo* application);
bool clearDisplayList(ApplicationInfo application);

#endif
