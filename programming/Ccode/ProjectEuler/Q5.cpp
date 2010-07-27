#include "Includes.h"


int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ4\n");
  time(&start);
  //START
  bool found=false;
  int max=1;
  int answer=0;
  
  for(long long x=1;!found;x++){
    int num=0;
    bool d=true;
    for(int d=1;d<=20;d++){
      if(!(x%d)){
        num++;
      }
    }
    if(num>max){
      max=num;
      printf("New max (%d) at: %d\n",max,x);
    }
    if(num==20){
      answer=x;
      found=true;
    }
  }
  printf("Answer: %d\n",answer);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
