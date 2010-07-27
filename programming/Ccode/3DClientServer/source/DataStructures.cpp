#include "DataStructures.h"

dvector newdvector(const unsigned int dim) {
  dvector v;
  v = (double *)calloc(dim, sizeof(double));
  if (v==NULL) {
    printf("Not enough memory for new double vector of dimension %d\n",(dim+1));
  }
  return v;
}

cvector newcvector(const unsigned int dim) {
  cvector v;
  v = (char *)calloc(dim, sizeof(char));
  if (v==NULL) {
    printf("Not enough memory for new character vector of dimension %d",(dim+1));
  }
  return v;
}

ivector newivector(const unsigned int dim) {
  ivector v;
  v = (int *)calloc(dim, sizeof(int));
  if (v==NULL) {
    printf("Not enough memory for new integer vector of dimension %d",(dim+1));
  }
  return v;
}

/* DMATRIX*/
dmatrix newdmatrix(const unsigned int rows, const unsigned int cols) {
  dmatrix m;
  m = (double **)calloc(rows, sizeof(double*));
  if (m==NULL) {
    printf("Not enough memory for new double matrix");
  }
  for (unsigned int i=0; i<rows; i++) {
    m[i]= newdvector(cols);
  }
  return m;
}

void printdmatrix(const dmatrix m, const unsigned int rows, const unsigned int cols) {
  for (unsigned int r=0; r<rows; r++) {
    for (unsigned int c=0; c<cols; c++) {
      printf("%f\t",m[r][c]);
    }
    printf("\n");
  }
}

/* IMATRIX*/
imatrix newimatrix(const unsigned int rows, const unsigned int cols) {
  imatrix m;
  m = (int **)calloc(rows, sizeof(int*));
  if (m==NULL) {
    printf("Not enough memory for new integer matrix");
  }
  for (unsigned int i=0; i<rows; i++) {
    m[i]= newivector(cols);
  }
  return m;
}

void printimatrix(const imatrix m, const unsigned int rows, const unsigned int cols) {
  for (unsigned int r=0; r<rows; r++) {
    for (unsigned int c=0; c<cols; c++) {
      printf("%d\t",m[r][c]);
    }
    printf("\n");
  }
}

/* CMATRIX*/
cmatrix newcmatrix(const unsigned int rows, const unsigned int cols) {
  cmatrix m;
  m = (char **)calloc(rows, sizeof(char*));
  if (m==NULL) {
    printf("Not enough memory for new char matrix");
  }
  for (unsigned int i=0; i<rows; i++) {
    m[i]= newcvector(cols);
  }
  return m;
}

void printcmatrix(const cmatrix m, const unsigned int rows, const unsigned int cols) {
  for (unsigned int r=0; r<rows; r++) {
    for (unsigned int c=0; c<cols; c++) {
      printf("%c\t",m[r][c]);
    }
    printf("\n");
  }
}


void freevector(void *v) {
  free(v);
}

void freematrix(void **m, const unsigned int rows) {
  for (unsigned int i=0; i<rows; i++) {
    free(m[i]);
  }
  free(m);
}

void deldmatrix(dmatrix m, const unsigned int rows) {
  freematrix((void**)m,rows);
}

void delcmatrix(cmatrix m, const unsigned int rows) {
  freematrix((void **)m,rows);
}

void delimatrix(imatrix m, const unsigned int rows) {
  freematrix((void **)m,rows);
}
