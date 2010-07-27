#include "includes.h"
#ifndef __MYAPPLICATION_H__
#define __MYAPPLICATION_H__

class myapplication{
  public:
    myapplication();
    void run(void);
    bool running(void);
    int getresolution(void);
    double gettimepassed(void); 
    void settimepassed(double passed); 
    void printtime(void);
    void updatetime(void);
    void shutdown(void);

    pthread_mutex_t timemutex,syscallmutex,netcallmutex;
    pthread_cond_t timecondition,syscallcondition,netcallcondition;
    pthread_t thread1, thread2, thread3, thread4;

    clock_t previous, now;    
    
  private: 
    int clocktime(void);
    void print_now(void);
    
    int sec,min,hour,day;
    double timepassed;
    bool runstatus;
    int resolution;
};
#endif
