/**
 * \file BASE/myio.h
 * \brief Header file, for BASE/myio.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef myio_H_
  #define myio_H_
  
  #include "BASE.h"
 
  /**
  * \brief The myio class<br>
  *
  * TODO Description<br>
  * bugs: none found
  */
  class myio : public object{
    public:
      myio();
      vector<string> filesindir(string dirpath,string fileextension);
      vector<string> dirsindir(string dirpath);
      ~myio();

    private:
      //Variables
      struct dirent*          direntry_ptr;
      //Functions
      bool   isfile(const char *name);
      bool   isdir(const char *name);
      bool   ends_with(const char *haystack, const char *needle);
      bool   contains(const char *haystack, const char *needle);
  };

#endif
