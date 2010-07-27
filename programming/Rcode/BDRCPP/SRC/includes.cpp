#include "includes.h"

void *calloc_init(size_t num, size_t size){
  void *buf;
  buf = R_chk_calloc(num,size);
  if (buf) memset(buf,0,num*size);
  return buf;
}
