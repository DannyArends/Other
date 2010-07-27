#include "includes.h"
#ifndef __SDLCOMMON_H__
#define __SDLCOMMON_H__

int makeargv(char *s,const char *delimiters, char ***argvp);
void freemakeargv(char **argv);

#endif
