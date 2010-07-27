#include "Includes.h"

int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ1\n");
  time(&start);
  //START
  int sum=0;
  
  for(int x=0;x<1000;x++){
    if(!(x%3) || !(x%5)){
      sum += x;
    }
  }
  printf("Answer: %d\n",sum);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
