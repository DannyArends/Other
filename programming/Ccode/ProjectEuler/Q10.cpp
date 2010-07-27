#include "Includes.h"

bool is_even(int tocheck){
  return(!(tocheck%2));
}

bool is_prime(int tocheck){
  //Bruteforce is_prime
  if(tocheck>2 && is_even(tocheck)) return false;
  for(int x=3;x<(tocheck/2);x++){
    if(!(tocheck%x)){ return false;}
  }
  return true;
}

int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ7\n");
  time(&start);
  //START
  int answer=0;

  printf("Answer: %llu\n",answer);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
