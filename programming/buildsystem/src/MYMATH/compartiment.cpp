/**
 * \file MYMATH/compartiment.cpp
 * \brief Code file, Implementation of class: \ref compartiment
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "compartiment.h"

compartiment::compartiment(){

}

compartiment::~compartiment(){
  for(uint i = 0; i < subcompartiments.size(); i++){
    delete subcompartiments[i];
  }
}

