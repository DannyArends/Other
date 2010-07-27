#include "Includes.h"


bool is_even(int tocheck){
  return(tocheck%2==0);
}

int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ2\n");
  time(&start);
  //START
  int sum       =0;
  int previous  =1;
  int current   =2;
  
  while(current<4000000){
    int temp = current;
    current=previous+current;
    previous=temp;
    if(is_even(temp)) sum+=temp;
    printf("%d %d\n",temp,is_even(temp));
  }
  printf("Answer: %d\n",sum);
  
  //END
  time(&end);
  timediff = difftime(start, end);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
