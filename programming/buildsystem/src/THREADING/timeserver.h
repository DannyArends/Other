/**
 * \file THREADING/timeserver.h
 * \brief Header file, for THREADING/timeserver.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef TIMESERVER_H_
  #define TIMESERVER_H_
  #include "THREADING.h"

  /**
  * \brief Structure holding time and/or timer information
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  typedef struct timeinfo{
    clock_t now;
    clock_t previous;
    int sec,min,hour,day;
  } timeinfo;
  
  int timedifference(clock_t t1,clock_t t2);

  /**
  * \brief Timed objects are children of a timeserver and fire every interval secs.
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class timedobject{
      public:
      timedobject(){  this->interval = 1; }
      void setinterval(uint interval){this->interval=interval;}
      uint getinterval(void){return this->interval;}
      void setparent(timedobject* p){};
      virtual void timedtask()=0;
      virtual ~timedobject(){ }
      private:
      uint interval;
  };

  /** 
  * \brief Threaded monitoring of time in second resolution.
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class timeserver: public node<timedobject>{
    public:
      timeserver();
      string printtime(void);
      void inittime(void);
      void updatetime(void);
      void pauze(void);
      void resume(void);
      void shutdown(void);
      
      timeinfo    time;
      bool        running;
      bool        monitoring;
    private:
      pthread_t   timethread;       //Monitor time
      int         returnvalue;
  };

#endif
