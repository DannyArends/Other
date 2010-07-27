#include "individuals.h"

void converttomarker(const char* possiblemarker){

}

void loadindividuals(const char* filename,int nummarkers,int numindividuals){
  std::string in;
  int columncount=0;
  int rowcount=0;  
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() && rowcount < numindividuals){
      myfile >> in;
      if(columncount==0){
        printf("\t\t%d %s:",rowcount,in.c_str());
      }else{
        printf(" %s",in.c_str());
        converttomarker(in.c_str());
      }
      columncount++;
      if(columncount==nummarkers+1){
        printf("\n");
        columncount=0;
        rowcount++;
      }
    }
  }
  myfile.close();
}
