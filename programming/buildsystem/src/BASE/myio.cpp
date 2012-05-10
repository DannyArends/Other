/**
 * \file BASE/myio.cpp
 * \brief Code file, Implementation of class: \ref myio
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "myio.h"

/**
* Class used to save objects to an io stream<br>
* bugs: none found
*/
myio::myio(){

}

vector<string> myio::filesindir(string dirpath,string fileextension){
  DIR*      dir_ptr;
  dir_ptr = opendir(dirpath.c_str());
  vector<string> matchingfiles;

  while ((direntry_ptr=readdir(dir_ptr)) != NULL){
    char* name = direntry_ptr->d_name;
    if(isfile(name) && ends_with(name,fileextension.c_str())){
      matchingfiles.push_back((string)name);
    }
  }
  closedir(dir_ptr);
  return matchingfiles;
}

vector<string> myio::dirsindir(string dirpath){
  DIR*      dir_ptr;
  dir_ptr = opendir(dirpath.c_str());
  vector<string> matchingdirs;

  while ((direntry_ptr=readdir(dir_ptr)) != NULL){
    char* name = direntry_ptr->d_name;
    if(isdir(name)){
      matchingdirs.push_back((string)name);
    }
  }
  closedir(dir_ptr);
  return matchingdirs;
}

bool myio::isfile(const char *name){
  if(name==NULL) return false;
  return contains(name,".") && !(ends_with(name,".") || ends_with(name,".."));
}

bool myio::isdir(const char *name){
  if(name==NULL) return false;
  return !contains(name,".") && !(ends_with(name,".") || ends_with(name,".."));
}

bool myio::contains(const char *haystack, const char *needle){
    const char *found = strstr(haystack, needle);
    return found > 0;
}

bool myio::ends_with(const char *haystack, const char *needle){
    const char *found = strstr(haystack, needle);
    return found && found[strlen(needle)] == 0;
}

myio::~myio(){

}

