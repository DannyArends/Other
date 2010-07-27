#include "population.h"
#include "markers.h"

void loadpopulation(speciestype species, const char* filename){
  int numgenerations;
  std::string parameter;
  std::string formula;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    myfile >> parameter >> numgenerations;
    for(int x=0;x<numgenerations;x++){
      myfile >> parameter >> formula;
      printf("   Generation %d: using %s markers with formula %s\n",x,parameter.c_str(),formula.c_str());
      loadmarkertype(parameter.c_str());
      parsepopulationformula(species, formula.c_str());
    }
  }
  myfile.close();
}

void parsepopulationformula(speciestype species, const char* formula){
  for(int x=0;formula[x] != '\0';x++){
    switch(formula[x]){
  		case BLEFT:{
  			printf("(");
  		} break;
  		case BRIGHT:{
  			printf(")");
  		} break;
  		case CROSS:{
  			printf(" * ");
  		} break;
  		case AND:{
  			printf(" + ");
  		} break;
  		default:{
  			printf("%c",formula[x]);
  		} break;
    }
  }
  printf("\n");
}

