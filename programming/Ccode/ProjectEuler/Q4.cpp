#include "Includes.h"


int length(int tocheck){
  //Length of an integer
  int i = 0;
  while(tocheck!=0){
    tocheck = tocheck/10;
    i++;
  }
  return i;
}

int palindrome(int tocheck,int length){
  int *array;
  array = (int*)malloc(length * sizeof(int));
  bool ispalindrome = true;
  for(int x=0;x<length;x++){
    array[x]=tocheck%10;
    tocheck = tocheck/10;
  }
  for(int x=0;x<length;x++){
    if(array[x]!=array[length-(x+1)]) ispalindrome = false;
  }
  free((void*)array);
  return ispalindrome;
}

int main(int argc,char *argv[]) {
  double timediff=0;
  time_t start,end;
  freopen("CON", "w", stdout); 
  printf("\n\nQ4\n");
  time(&start);
  //START
  int num=0,highest=0,l=0;
  for(int x=100;x<999;x++){
    for(int y=100;y<999;y++){
    num = x*y;
    l = length(num);
      if(num > highest && palindrome(num,l)){
        printf("palindrome: %d\n",num);
        highest=num;
      }
    }
  }
  printf("Answer: %d\n",highest);
  
  //END
  time(&end);
  timediff = difftime(end, start);
  printf("Execution Time: %f\n",timediff);
  exit(0);
}
