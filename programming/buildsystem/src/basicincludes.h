/**
 * \file basicincludes.h
 * \brief Header file, limited use of main c and c++ includes
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef BASICINCLUDES_H_
  #define BASICINCLUDES_H_
  #include <cstdio>
  #include <cstdlib>
  #include <cfloat>
  #include <climits>
  #include <iostream>
  #include <fstream>
  #include <sstream>
  #include <string.h>
  #include <string>
  #include <vector>
  #include <cmath>
  #include <map>
  #include <algorithm>
  #include <set>
  #include <list>
  #include <iostream>
  #include <typeinfo>
  #include <exception>

  //GLOBAL DEFINES AND TYPEDEFS
  typedef unsigned int uint;

  #define message(format, ...) {\
    printf(format, ## __VA_ARGS__);printf("\n"); \
  }

  #define PI 3.14159265

  using namespace std;

#endif
