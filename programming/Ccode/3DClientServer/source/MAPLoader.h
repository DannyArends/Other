#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__
#include "includes.h"
#include "DataStructures.h"
#include "Error.h"
#include "FileIO.h"

void setMap(ApplicationInfo* application,const char* name);
bool loadmapfromfile(ApplicationInfo *application,const int number,const char *filename);
void loadMaps(ApplicationInfo *application);

#endif
