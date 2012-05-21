/**
 * \file BASE/lsystem.cpp
 * \brief Code file, Implementation of class: \ref lsystem
 *
  * Threaded keyboard support (unused, when using GUI)<br>
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "lsystem.h"

template<class element, class sequence>
lsystem<element, sequence>::lsystem(){
}

template<class element, class sequence>
lsystem<element, sequence>::~lsystem(){
   for(uint i = 0; i < rules.size(); i++){
      delete rules[i];
   }
}

template<class element, class sequence>
void lsystem<element, sequence>::addRule(element hd, sequence tl){
   rules.push_back(new lsystemrule(hd, tl));
}

template<class element, class sequence>
sequence lsystem<element, sequence>::replace(element hd){
   static sequence seq;

   seq.clear();
   for(uint i = 0; i < rules.size(); i++){
      if(rules[i]->isMatch(hd)){
        return rules[i]->getTail();
      }
   }
   seq.push_back(hd);
   return seq;
}

template<class element, class sequence>
void lsystem<element, sequence>::iterate(){
   sequence newstate;

   for(uint i = 0; i < state.size(); i++)   {
      sequence replacement = replace(state[i]);
      for(uint e = 0; e < replacement.size(); e++){
         newstate.push_back(replacement[e]);
      }
  }
  state = newstate;
}

void initLSystem(){
  lsystem<char, string> test;

  test.setState("X");
  test.addRule('X', "F-[[X]+X]+F[+FX]-X");
  test.addRule('F', "FF");
  for(int i = 0; i < 10; i++)   {
    test.iterate();
    //printf("state%d: %s\n",i,test.getState().c_str());
  }
}
