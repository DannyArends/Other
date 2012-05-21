/**
 * \file BASE/lsystem.h
 * \brief Header file, for BASE/lsystem.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef LSYSTEM_H_
  #define LSYSTEM_H_
  #include "BASE.h"

  
  /** 
  * \brief Class holding the lsystem (current state and rules)
  */
  template<typename element, class sequence>       
  class lsystem{
  
    /** 
            * \brief Class representing a single rule in out lsystem
            */
    class lsystemrule{
    public:
      lsystemrule(element hd, sequence tl) {
        head = hd; 
        tail = tl;
      }
      
      bool isMatch(element hd) {
        return hd == head;
      }
      
      sequence getTail() {
        return tail;
      }
    private:
    element head;
    sequence tail;
    };
  
  public:
    lsystem();
    ~lsystem();
    void setState(sequence st) {
      state = st;
    }
    sequence getState() {
      return state;
    }
   
    void addRule(element hd, sequence tl);
   
    sequence replace(element hd);
    void iterate();
  private:
    sequence state;
    vector<lsystemrule*> rules;
  };
  
  void initLSystem();
#endif
