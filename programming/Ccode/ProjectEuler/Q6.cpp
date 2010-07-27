#include "Includes.h"



typedef struct bigint{
  unsigned int*  number;
  unsigned int   length;
};

int lengthof(int tocheck){
  int i = 0;
  while(tocheck!=0){
    tocheck = tocheck/10;
    i++;
  }
  if(i==0) i=1;
  return i;
}

int lengthof(bigint tocheck){
  return tocheck.length;
}

bigint newbigint(int num){
  int length = lengthof(num);
  bigint b;
  b.number = (unsigned int*)malloc(length*sizeof(unsigned int));
  b.length = length;
  for(int x=0;x<length;x++){
    b.number[x]=num%10;
    num=num/10;
  }
  return b;
}

bigint resize(bigint toresize,int length){
  bigint b;
  b.number = (unsigned int*)malloc(length*sizeof(unsigned int));
  b.length = length;
  for(unsigned int x=0;x<length;x++){
    if(toresize.length>x){
      b.number[x] = toresize.number[x];
    }else{
      b.number[x] = 0;
    }
  }
  return b;
}

bigint shrink(bigint toresize){
  int cnt = 0;
  bool begin = false; 
  for(unsigned int x=(toresize.length-1);!begin && x >0;x--){
    if(toresize.number[x]==0){
      cnt++;
    }else{
      begin = true;
    }
   
  }
  int newlength = toresize.length-cnt;
  if(newlength > 0) toresize = resize(toresize,newlength);
  return toresize;
}

void printbigint(bigint x){
  for(int c=(x.length-1);c>=0;c--){
    printf("%d",x.number[c]);
  }
  printf(":%d",x.length);
}

bigint add(bigint x,bigint y){
  bigint b;
  int maxlength;
  maxlength = x.length>y.length ? x.length : y.length;
  x = resize(x,(maxlength+1));
  y = resize(y,(maxlength+1));
  b.number = (unsigned int*)malloc((maxlength+1)*sizeof(unsigned int));
  b.length = (maxlength+1);  
  bool transfer=false;
  for(int c=0;c<(maxlength+1);c++){
    b.number[c] =  (x.number[c] + y.number[c]+transfer)%10;
    if((x.number[c] + y.number[c] + transfer)>=10){
      transfer=true;
    }else{
      transfer=false;
    }
  }
  return shrink(b);
}

bool equals(bigint x,bigint y){
  if(x.length!=y.length) return false;
  for(int c=0;c<x.length;c++){
    if(x.number[c] != y.number[c]) return false;
  }
  return true;
}


int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ6\n");
  time(&start);
  //START
  int answer=0;
  bigint sum;
  sum = newbigint(0);
  for(bigint x=newbigint(0);!equals(x,newbigint(2));x = add(x,newbigint(250000))){
    printbigint(x);
    printf(" + ");
    printbigint(sum);
    printf(" = ");
    sum = add(sum,x);
    sum = add(sum,sum);
    printbigint(sum);
    printf("\n");    
  }
  //printbigint(r);
  printf("Answer: \n");
  printbigint(sum);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
