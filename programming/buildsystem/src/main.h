/**
 * \file main.h
 * \brief Header file, for main.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
#ifndef MAIN_H_
  #define MAIN_H_
  #include "includes.h"
  #include "THREADING/THREADING.h"
  #ifdef USE_MATH
    #include "MYMATH/MYMATH.h"
  #endif
  #ifdef USE_GAME
    #include "GAME/GAME.h"
  #endif
  #ifdef USE_NETWORK
    #include "NETWORK/NETWORK.h"
  #endif
  #ifdef USE_GUI
    #include "GUI/GUI.h"
  #endif

  #include "application.h"

#endif

