#include "species.h"

int str2int(const char* str) {
  int n;
  sscanf(str,"%d",&n);
  return n;
}

speciestype loadspecies(const char* filename){
  speciestype r;
  std::string parameter;
  std::string name;
  int nchr;
  int ploid;
  std::string sex;
  int sextype;
  
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() ){
      myfile >> parameter >> name;
      r.name = name.c_str();
      myfile >> parameter >> nchr;
      r.numchromosomes = nchr;
      myfile >> parameter >> ploid;
      r.numalleles = ploid;
      myfile >> parameter >> sex;
      if(sex.c_str()[0]=='N'){
        r.sex = -1;
      }else{
        r.sex = str2int(sex.c_str());
      }
      myfile >> parameter >> sextype;
      r.sextype = (sextypes)sextype;
      printf("   Species:%s\n   Chromosomes:%d %d\n   Sex:%d %d\n",r.name,r.numchromosomes,r.numalleles,r.sex,r.sextype);
    }
  }
  myfile.close();
  return r;
}
