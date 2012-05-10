/**
 * \file THREADING/mythread.cpp
 * \brief Code file, Implementation of class: \ref mythreader
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "THREADING.h"

/**
* C-routine that is executed in the started thread to wrap the execution of the runtask method<br>
* Randomnumbers are made unique by setting the randomnumber seed using the threadstarttime<br>
* This function uses a clock_t to time the execution of the thread, which is reported on finish on std_out<br>
* bugs: none found<br>
* @param ptr taskholderobject casted in as a void*<br>
*/
void* runtask(void* ptr){
  srand ( time(NULL) );
  taskholder* taskh = (taskholder*)ptr;
  clock_t s = clock();
  taskh->runtask();
  clock_t e = clock();
  cout << "Thread took "<< timedifference(s, e) << " msecs" << endl;
  pthread_exit((void*) 0);
  return((void*) 0);
}

/** 
* The mythreader class is loadable with a taskholderobject, after which is can be used to execute the taskholderobjects runtask method in a seperate thread.<br>
* The execution of the task is timed, and reported on the stdout<br>
* bugs: none found
*/
mythreader::mythreader(){
  this->running=false;
}

/** 
* bugs: none found
*/
mythreader::~mythreader(){
  this->running=false;
}

/**
* loads a taskholderobject<br>
* bugs: none found<br>
* @param toload taskholderobject that is attach to the start() function<br>
*/
void mythreader::addload(taskholder* toload){
  this->mytask=toload;
}

/**
* start a seperate thread and execute the taskholderobjects runtask method<br>
* bugs: none found<br>
*/
void mythreader::start(){
  this->running=true;
  this->returnval = pthread_create(&this->rthread, NULL, runtask, (void*) this->mytask);
  this->running=false;
}

