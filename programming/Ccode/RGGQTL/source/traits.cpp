#include "traits.h"

void loadtraits(const char* filename,int numindividuals,int numtraits){
  std::string in;
  double traitvalue;
  int colcount=0;
  int rowcount=0;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() && rowcount < numindividuals){
      if(colcount==0) printf("\t");
      if(rowcount==0){
        myfile >> in;
        printf("\t%s",in.c_str());
      }else{
        myfile >> traitvalue;
        printf("\t%.2f",traitvalue);
      }
      colcount++;
      if(colcount==numtraits){
        printf("\n",rowcount);
        colcount=0;
        rowcount++;
      }
    }
  }
  myfile.close();
}


double getvariance(int traitnum){
  double variance = 0.0;
  
  return variance;
}

double getmean(int traitnum){
  double mean = 0.0;
  
  return mean;
}
