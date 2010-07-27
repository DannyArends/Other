#include "includes.h"
#include "error.h"
#include "species.h"
#include "population.h"
#include "individuals.h"
#include "markers.h"
#include "traits.h"
#include "cofactors.h"

static struct option long_options[] = {
  {"file",       optional_argument, 0,  'f'},
  {"alpha",      optional_argument, 0,  'a'},
  {"modelmethod",optional_argument, 0,  'm'},
  {"scanmethod", optional_argument, 0,  's'},
  {0, 0, 0, 0}
};

typedef struct{
  populationtype* supportedpopulations;
  speciestype* supportedspecies;
  markertype* supportedmarkers;
  bool error;
} application;

typedef struct{
  int numpopulations;
  int* populationsizes;
	int numindividuals;
  int nummarkers;
  int numtraits;
  int numcofactors;
  speciestype species;
  populationtype population;
  individualtype* individuals;
} qtlinput;

typedef struct{
	int id;
} qtlmodel;

typedef struct{
	int id;
} qtlscan;

qtlinput readinputfile(char* filename){
  qtlinput r;
  std::string parameter;
  std::string value;
  int number;
  int sum=0;
  std::ifstream myfile (filename);
  if (myfile.is_open()){
    while (! myfile.eof() ){
      myfile >> parameter;
      if(strcmp(parameter.c_str(),"Species:")==0){
        myfile >> number >> value;
        printf("  Species file: %s\n", value.c_str());
        r.species = loadspecies(value.c_str());
      }
      if(strcmp(parameter.c_str(),"Population:")==0){
        myfile >> number >> value;      
        printf("  Population file: %s with %d populations\n", value.c_str(),number);
        r.numpopulations = number;
        r.populationsizes = new int[r.numpopulations];
        loadpopulation( r.species, value.c_str());
      }
      if(strcmp(parameter.c_str(),"Markers:")==0){
        myfile >> number >> value;      
        printf("  Marker file: %s with %d markers\n", value.c_str(),number);
        r.nummarkers = number;
        loadmarkers(value.c_str(),r.nummarkers);
      }      
      if(strcmp(parameter.c_str(),"Individuals:")==0){
        for(int x=0;x<r.numpopulations;x++){
          myfile >> number;
          r.populationsizes[x] = number;
          sum += number;
        }
        myfile >> value;
        printf("  Individual file: %s with %d individuals\n", value.c_str(),sum);
        r.numindividuals = sum;
        r.individuals = new individualtype[r.numindividuals];
        loadindividuals(value.c_str(),r.nummarkers,r.numindividuals);
      }
      if(strcmp(parameter.c_str(),"Traits:")==0){
        myfile >> number >> value;
        printf("  Trait file: %s with %d traits\n", value.c_str(),number);
        r.numtraits = number;
        loadtraits(value.c_str(),r.numindividuals,r.numtraits);
      }
      if(strcmp(parameter.c_str(),"Cofactors:")==0){
        myfile >> number >> value;
        printf("  Cofactor file: %s with %d cofactors\n", value.c_str(),number);
        r.numcofactors = number;
        loadcofactors(value.c_str(),r.numindividuals,r.numcofactors);       
      }
    }
  }
  myfile.close();
  return r;
}

void checkinputfile(qtlinput* data){

}

qtlmodel createqtlmodel(qtlinput data,scanmethod scan,double alpha){
  qtlmodel r;
  return r;
}

qtlscan scanqtlscan(qtlmodel data,scanmethod scan,double alpha){
  qtlscan r;
  return r;
}

void createreport(qtlinput data,qtlmodel model,qtlscan scan){

  return;
}

int main(int argc,char *argv[]) {
  bool verbose       = false;
  bool help          = false;
  char *filename     = NULL;
  char *logfile      = NULL;
  modelmethod model  = FORWARD;
  scanmethod scan    = FAST;
  double alpha       = 0.05;
  int option_index   = 0;
  char c;
 
  while ((c = getopt_long(argc, argv, "vho:f:m:a:s:",long_options, &option_index)) != -1){
    switch (c) {
    case 'v':
      verbose = true;
      break;
    case 'h':
      exit_help("\n");
      break;
    case 'o':
      logfile = optarg;
      break;      
    case 'f':
      filename = optarg;
      break;      
    case 'a':
      alpha = atof(optarg);
      break;
    case 'm':
      model = (modelmethod)optarg[0];
      break;
    case 's':
      scan = (scanmethod)optarg[0];
      break;      
    default:
      //printf("unknown option '%c'.\n", optopt);
      break;
    }
  }
  //Main program
  if (logfile==NULL){
    printf("  Running without a logfile.\n"); 
  }else{
    printf("  Logfile: %s\n",logfile);  
    FILE *stream; 
    stream = freopen(logfile, "w", stdout);     
  }
  printf("RGG v0.0\n");
  
  printf("Stage 0) Parameters\n");
  if (filename==NULL) exit_error("  Please supply a 'file argument'.\n"); else printf("  Filename: %s\n",filename);

  if (alpha <= 0 || alpha >=1) exit_help("  Please set alpha between 0 and 1.\n"); else printf("  Alpha: %.2f\n",alpha);
  if (model == FORWARD || model == BACKWARD) printf("  Model: %c\n",model); else exit_help("  Please set a valid modeling method (F or B).\n");
  if (scan == FAST  || scan == COMPLETE)printf("  Scan: %c\n",scan); else exit_help("  Please set a valid scanning method (F or C).\n");
  printf("Stage 1) Inputfile\n");
  printf("  Sub 1) Reading inputfile\n");
  qtlinput inputdata = readinputfile(filename);
  printf("  Sub 2) Checking inputfile\n");
  checkinputfile(&inputdata);
  printf("Stage 2) Modeling\n");
  qtlmodel modeldata = createqtlmodel(inputdata,FAST,alpha);
  printf("Stage 3) Scanning\n");
  qtlscan scandata = scanqtlscan(modeldata,scan,alpha);
  printf("Stage 3) Creating report\n");
  createreport(inputdata,modeldata,scandata);
  exit(0);
}
