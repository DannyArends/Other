#ifndef __ERROR_H__
#define __ERROR_H__
#include "includes.h"

void printhelp(void);
void exit_help(const char *msg);
void exit_error(const char *msg);
void error_nonfatal(const char *msg,const char *function);
#endif
