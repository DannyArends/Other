#include "cofactors.h"

void loadcofactors(const char* filename,int numindividuals,int numcofactors){
  std::string in;
  int colcount=0;
  int rowcount=0;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() && rowcount < numindividuals){
      myfile >> in;
      if(colcount==0) printf("\t");
      if(rowcount==0){
        //Cofactor names
        printf("\t%s",in.c_str());
      }else{
        //Cofactor  values
        printf("\t%s",in.c_str());
      }
      colcount++;
      if(colcount==numcofactors){
        printf("\n",rowcount);
        colcount=0;
        rowcount++;
      }
    }
  }
  myfile.close();
}

void setmarkerascofactors(void){

}
