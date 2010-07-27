#include "markers.h"

markertype loadmarkertype(const char* filename){
  markertype returnvar;
  std::string markert;
  double prob;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof()){
      myfile >> markert >> prob;
      printf("\t\t%s %.2f\n",markert.c_str(),prob);
    }
  }
  myfile.close(); 
 return returnvar;
}

void loadmarkers(const char* filename,int nummarkers){
  std::string name;
  int chr;
  double position;
  int count=0;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() && count < nummarkers){
      myfile >> name >> chr >> position;
      printf("\t\t%d %s %d %.2f\n",count,name.c_str(),chr,position);
      count++;
    }
  }
  myfile.close();
}
