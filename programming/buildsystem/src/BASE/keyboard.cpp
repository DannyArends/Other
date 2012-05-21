/**
 * \file BASE/keyboard.cpp
 * \brief Code file, Implementation of class: \ref keyboard
 *
  * Threaded keyboard support (unused, when using GUI)<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "keyboard.h"

void* monitorinput(void* ptr){
  keyboardinput* key = (keyboardinput*)ptr;
  string msg;
  while(key->running){
    cout << "[COMMAND]\t";
    getline(cin,msg);
    cout << "[EXECUTING]\t" << msg << endl;
    if(msg == "q" || msg == "quit"){
      strcpy(key->command,msg.c_str());
      key->running=false;
    }
    if(msg == "t" || msg == "time"){
      strcpy(key->command,msg.c_str());
    }
    if(msg == "i" || msg == "info"){
      strcpy(key->command,msg.c_str());
    }
    if(msg == "s" || msg == "set"){
      strcpy(key->command,msg.c_str());
    }
  }
  return((void*) 0);
}

/** 
* The keyboard class is monitoring stdin on a seperate thread.<br>
* bugs: none found
*/
keyboard::keyboard(keyboardinput* key){
  monitorinput((void*) key);
}
