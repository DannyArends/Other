/**
 * \file THREADING/timeserver.cpp
 * \brief Code file, Implementation of class: \ref timeserver
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#include "timeserver.h"

/**
* C-routine that calculates the difference between 2 clock_t structures<br>
* bugs: none found<br>
* @param t1 clock_t structure starttime<br>
* @param t2 clock_t structure endtime<br>
*/
int timedifference(clock_t t1,clock_t t2){
  return (int)((double)(t2 - t1) / CLOCKS_PER_SEC * 1000);
}

/**
* C-routine that monitors time in a thread, updates a timeserver structure<br>
* bugs: none found<br>
* @param ptr timeserver* casted in as a void*<br>
*/
void* monitortime(void* ptr){
  timeserver* timer = (timeserver*)ptr;
  cout << "[STARTUP]\tTime monitoring" << endl;
  timer->inittime();
  timer->time.previous = clock();
  while(timer->running){
    sleep(20);
    timer->time.now = clock();
    if(timer->monitoring && timedifference(timer->time.previous, timer->time.now) >= 1000.0){
      timer->updatetime();
      timer->time.previous = timer->time.now = clock();
    }  
  }
  pthread_exit((void*) 0);
  return((void*) 1);
}

/**
* The timeserver class uses a timeserver structure and a thread to monitor time in a failfree fashion at second resolution<br>
* bugs: none found<br>
*/
timeserver::timeserver(){
  this->running=true;
  this->monitoring=true;
  this->returnvalue = pthread_create(&this->timethread, NULL, monitortime, (void*) this);
}

/**
* prints the time since the timeserver started on the stdout<br>
* bugs: none found<br>
*/
string timeserver::printtime(){
  stringstream timeout;
  timeout << time.day << ":";
  timeout << time.hour << ":";
  if(time.min < 10){
    timeout << "0" << time.min << ":";
  }else{
    timeout << time.min << ":";
  }
  if(time.sec < 10){
    timeout  << "0" << time.sec << endl;
  }else{
    timeout << time.sec << endl;
  }
  return timeout.str();
}

/**
* Sets time to 0<br>
* bugs: none found<br>
*/
void timeserver::inittime(){
  time.sec=0;
  time.min=0;
  time.hour=0;
  time.day=0;
}

/**
* Called when a second is passed<br>
* bugs: none found<br>
*/
void timeserver::updatetime(){
  if(this->monitoring){
    time.sec++;
    for(uint a=0;a<this->getchildren().size();a++){
      if((time.sec%this->getchildren()[a]->getinterval()) == 0){
        this->getchildren()[a]->timedtask();
      }
    }
    if(time.sec==60){
      time.sec=0;
      time.min++;
    }
    if(time.min==60){
      time.min=0;
      time.hour++;
    }
    if(time.hour==24){
      time.hour=0;
      time.day++;
    }
  }
}

/**
* Shutdown time monitoring<br>
* bugs: none found<br>
*/
void timeserver::shutdown(void){
  this->running=false;
}

/**
* Pauzes time monitoring<br>
*
* TODO Description<br>
* bugs: none found.<br>
*/
void timeserver::pauze(void){
  this->monitoring=false;
}

/**
* Resumes time monitoring<br>
*
* TODO Description<br>
* bugs: none found.<br>
*/
void timeserver::resume(void){
  this->monitoring=true;
}
