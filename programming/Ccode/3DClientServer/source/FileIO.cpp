#include "FileIO.h"

bool ends_with(const char *haystack, const char *needle){
    const char *found = strstr(haystack, needle);
    return found && found[strlen(needle)] == 0;
}

int getnumfiles(const char* dirname,const char* extension){
  DIR *dir = opendir(dirname);
  struct dirent *dp;
  int i=0;
  int f=0;
  while ((dp=readdir(dir)) != NULL){
    i++;
    char *name = dp->d_name;
    if(ends_with(name, extension)){
      //printf("%d: %s\n",f,name);
      f++;
    }
  }
  printf("%d/%d files in %s matched extension %s\n",f,i,dirname,extension);
  closedir(dir);
  return f;
}

int getnumlines(const char *filename){
  FILE *fp = fopen(filename,"r"); 
  int nlines = 0;   
  char c;
  while((c=getc(fp))!=EOF){    
    if (c=='\n'){   
      nlines++;
    }
  }
  fclose(fp);
  printf("File %s contains %d lines\n",filename,nlines);
  return nlines;
}

char* getfilename(const char* dirname, const char* extension, const int number){
  DIR *dir = opendir(dirname);
  struct dirent *dp;
  int i=0;
  int f=0;
  char* filename = new char[50];
  while ((dp=readdir(dir)) != NULL){
    i++;
    char *name = dp->d_name;
    if(ends_with(name, extension)){
      if(f==number){
        sprintf(filename,"%s/%s",dirname,name);
        //printf("%d: %s\n",f,filename);
        return filename;
      }
      f++;
    }
  }
  printf("Error: Cant select %d/%d in %s\n",number,f,dirname);
  closedir(dir);
  return (char*)"NOTFOUND";
}


