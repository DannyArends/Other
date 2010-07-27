#ifndef __FILEIO_H__
#define __FILEIO_H__
#include "includes.h"

int getnumfiles(const char* dirname,const char* extension);
int getnumlines(const char* filename);
char* getfilename(const char* dirname,const char* extension,const int number);
#endif
