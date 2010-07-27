#include "Error.h"

void printhelp(void) {
  printf ("Commandline switches:\n");
  printf ("-h          This help.\n");
  printf ("-v          Verbose (produce a lot of textoutput).\n");
}

void exit_help(const char *msg) {
  printf(msg);
  printhelp();  
  exit(0);
}

void exit_error(const char *msg) {
  printf(msg);
  exit(1);
}

void error_nonfatal(const char *msg,const char *function) {
  printf("ERROR in %s: %s",function,msg);
}
