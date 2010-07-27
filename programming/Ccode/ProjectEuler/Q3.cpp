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
  printf("\n\nQ3\n");
  time(&start);
  //START
  //unsigned long long tofactor = 600851475143LL;
  unsigned long long tofactor = 2520;
  int largestprime  = 1;
  
  for(int x=2;(tofactor!=1);x++){
    if(is_prime(x) && !(tofactor%x)){
      int cnt=0;
      largestprime=x;
      while(!(tofactor%x)){
        tofactor = tofactor/x;
        cnt++;
      }
      printf("New prime factor: %d * %d %d\n",largestprime,cnt,tofactor);
      
    }
  }
  printf("Answer: %d\n",largestprime);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
