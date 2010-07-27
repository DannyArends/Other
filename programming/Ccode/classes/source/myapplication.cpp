#include "myapplication.h"

myapplication::myapplication(){
  this->sec=0;
  this->min=0;
  this->hour=0;
  this->day=0;
  this->resolution = clocktime();
}

void myapplication::run(void){
  cout << "Running" << endl;
  this->runstatus = true;
  previous = now = clock();
  pthread_mutex_init(&timemutex, NULL);
  pthread_cond_init (&timecondition, NULL);
  pthread_mutex_init(&syscallmutex, NULL);
  pthread_cond_init (&syscallcondition, NULL);
}

void myapplication::shutdown(void){
  cout << "Shutting down" << endl;
  this->runstatus = false;
  pthread_cond_signal(&timecondition);
  pthread_cond_signal(&syscallcondition);
  pthread_cond_signal(&netcallcondition);    
}

bool myapplication::running(void){
  return this->runstatus;
}

int myapplication::getresolution(void){
  return this->resolution;
}

double myapplication::gettimepassed(void){
  return this->timepassed;
}

void myapplication::settimepassed(double passed){
  this->timepassed = passed;
}


void myapplication::printtime(void){
  cout << "Online for: ";
  if(this->day != 0) cout << this->day << " day(s), ";
  if(this->hour != 0) cout << this->hour << " hour(s), ";
  if(this->min < 10){
    cout << "0" << this->min << " minute(s), ";
  }else{
    cout << this->min << " minute(s), ";
  }
  if(this->sec < 10){
    cout  << "0" << this->sec << " second(s)" << endl;
  }else{
    cout << this->sec << " second(s)" << endl;
  }
}

void myapplication::updatetime(void){
  this->sec++;
  if(this->sec==60){
    this->sec=0;
    this->min++;
  }
  if(this->min==60){
    this->min=0;
    this->hour++;
  }
  if(this->hour==24){
    this->hour=0;
    this->day++;
  }
}

int myapplication::clocktime(void){
  clock_t t1, t2;
  t1=t2=clock();  
  while(t1 == t2){
    t2 = clock();
  }
  cout << "Timing information" << endl;
  cout << "Clocks_per_sec: " << CLOCKS_PER_SEC << endl;
  cout << "Resolution: " << (double)(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
  return (int)((double)(t2 - t1) / CLOCKS_PER_SEC * 1000);
}

void myapplication::print_now(void){
  time_t rawtime;
  struct tm* timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  printf("%s",asctime(timeinfo));
  return;
}
