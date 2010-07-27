#include "includes.h"
#include "error.h"
#include "myapplication.h"
#include "myhttpserver.h"

static struct option long_options[] = {
  {0, 0, 0, 0}
};


myapplication myapp;

void* userinput(void* ptr){
  long my_id = (long)ptr;
  printf("Starting userinput monitoring on id %d at %d\n", my_id, pthread_self());
  string msg;
  while(myapp.running()){
    //SDL_Delay(myapp.getresolution()); 
    cin >> msg;
    if(msg=="q"){
      myapp.shutdown();
    }
    if(msg=="t"){
     myapp.printtime();
    }
  }
  pthread_exit((void*) 0);
}

void* timer(void* ptr){
  long my_id = (long)ptr;
  printf("Starting timer on id %d at %d\n", my_id, pthread_self());
  while(myapp.running()){
    SDL_Delay(myapp.getresolution());
    pthread_mutex_lock(&myapp.timemutex);
    myapp.now = clock();
    myapp.settimepassed((double)(myapp.now - myapp.previous) / CLOCKS_PER_SEC * 1000);
    if(myapp.gettimepassed() >= 1000.0){
      pthread_cond_signal(&myapp.timecondition);
      myapp.previous = myapp.now = clock();
    }
    pthread_mutex_unlock(&myapp.timemutex);
  }
  pthread_exit((void*) 0);
}

void* watchtimer(void* ptr){
  long my_id = (long)ptr;
  printf("Starting timer-watch on id %d at %d\n", my_id, pthread_self());
  while(myapp.running()){
    pthread_mutex_lock(&myapp.timemutex);
    pthread_cond_wait(&myapp.timecondition, &myapp.timemutex);
    myapp.updatetime();
    pthread_mutex_unlock(&myapp.timemutex);
  }
  pthread_exit((void*) 0);
}

void* systemcaller(void* ptr){
  long my_id = (long)ptr;
  printf("Starting systemcaller on id %d at %d\n", my_id, pthread_self());
  while(myapp.running()){
    pthread_mutex_lock(&myapp.syscallmutex);
    pthread_cond_wait(&myapp.syscallcondition, &myapp.syscallmutex);
    //TODO:SystemCaller
    pthread_mutex_unlock(&myapp.syscallmutex);
  }
  pthread_exit((void*) 0);
}

void* sdlserver(void* ptr){
  long my_id = (long)ptr;
  printf("Starting sdlserver on id %d at %d\n", my_id, pthread_self());
  while(myapp.running()){
    pthread_mutex_lock(&myapp.netcallmutex);
    pthread_cond_wait(&myapp.netcallcondition, &myapp.netcallmutex);
    //TODO:SDLCaller
    pthread_mutex_unlock(&myapp.netcallmutex);
  }
  pthread_exit((void*) 0);
}

int main(int argc,char *argv[]) {
  bool verbose       = false;
  bool help          = false;
  int option_index   = 0;
  char c;  
  FILE *stream;
  stream = freopen("CON", "w", stdout);
  printf("\nProgram v0.0\n");
  while ((c = getopt_long(argc, argv, "vh",long_options, &option_index)) != -1){
    switch (c) {
    case 'v':
      verbose = true;
      break;
    case 'h':
      help = true;
      break;
    default:
      //printf("unknown option '%c'.\n", optopt);
      break;
    }
  }
  if(help){
    exit_help("\n");
  }else{
    //Main program
    myapp.run();
    server s;
    
    long t1=1, t2=2, t3=3,t4=4;
    int  iret1, iret2,iret3,iret4;    /* Create independent threads each of which will execute function */
    iret1 = pthread_create( &myapp.thread1, NULL, userinput, (void*) t1);
    iret2 = pthread_create( &myapp.thread2, NULL, timer, (void*) t2);    
    iret3 = pthread_create( &myapp.thread3, NULL, watchtimer, (void*) t3);
    iret4 = pthread_create( &myapp.thread4, NULL, serverstart, (void*) &s);

    pthread_join( myapp.thread1, NULL);
    pthread_join( myapp.thread2, NULL);
    pthread_join( myapp.thread3, NULL);
    pthread_join( myapp.thread4, NULL);
    printf("Thread 1 returned: %d\n",iret1);
    printf("Thread 2 returned: %d\n",iret2);
    printf("Thread 3 returned: %d\n",iret3);
    printf("Thread 4 returned: %d\n",iret4);
    pthread_mutex_destroy(&myapp.timemutex);
    pthread_cond_destroy(&myapp.timecondition);
    pthread_mutex_destroy(&myapp.syscallmutex);
    pthread_cond_destroy(&myapp.syscallcondition);
  }
  exit(0);
}
