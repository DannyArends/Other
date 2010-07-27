#include "includes.h"
#include "interface.h"

int main(int argc,char *argv[]) {
  int argcc = argc;
  printf("Hello from main in c++\n");
  Smain(&argcc,argv);
  exit(0);
}
