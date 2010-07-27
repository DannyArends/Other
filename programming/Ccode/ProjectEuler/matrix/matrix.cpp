#include "includes.h"


typedef struct {
  uint nrows;
  name* rownames;
  uint ncols;
  name* colnames;
  intmatrix data;
}intmatrixobj;

typedef struct {
  uint nitems;
  name* names;
  intarray data;
}intvectorobj;

typedef struct {
  uint nrows;
  name* rownames;
  uint ncols;
  name* colnames;
  doublematrix data;
}doublematrixobj;

typedef struct {
  uint nitems;
  name* names;
  doublearray data;
}doublevectorobj;


void writeintmatrixobj_txt(char* filename, intmatrixobj matrix){

}


intmatrixobj readintmatrixobj_txt(char* filename){

}

void writedoublematrixobj_txt(char* filename, doublematrixobj matrix){

}


intmatrixobj readdoublematrixobj_txt(char* filename){

}





int main(int argc,char *argv[]) {
  printf("\nmatrix\n");

  exit(0);
}
