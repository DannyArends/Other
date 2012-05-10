/**
 * \file THREADING/THREADING.h
 * \brief Header file, for the THREADING directory
 *
 * This class is used to share the objects within the THREADING directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef THREADING_H_
  #define THREADING_H_

  #include "includes.h"
  //ALL DEPENDENCIES FOR THIS LIBRARY
  using namespace std;
  #ifdef WINDOWS
    #include <pthread/pthread.h>    /* POSIX Threads for windows */
  #endif
  class timeserver;
  class timedobject;
  
  /** 
  * \brief The superclass of all objects with threadable workloads.
  *
  * TODO Description<br>
  * bugs: none found
  */
  class taskholder{
    public:
      taskholder(){
      }

      virtual ~taskholder(){
      }

      virtual void runtask(void){
      }
  };
  
  /** 
  * \brief Provides threaded execution of a taskholder class.
  *
  * TODO Description<br>
  * bugs: none found
  */
  class mythreader{
    public:
      mythreader(void);
     ~mythreader(void);
     void addload(taskholder* toload);
     void start();
     
    protected:
      taskholder* mytask;
      pthread_t   rthread;
      bool running;
      int returnval;
  };

  #include "timeserver.h"
  
#endif
