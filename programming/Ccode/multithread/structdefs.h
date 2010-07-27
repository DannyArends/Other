
struct environment{
  string operatingsystem;
  string path;
  string time;
}

struct threaded{
  int                 status;
  pthread_t           thread;
}

struct timeserver{
  threaded            obj;
  clock_t             previous;
  clock_t             now;
  int                 day, hour, min, sec;
}

struct serverinput{
  threaded            obj;

}


struct application{
  environment env;
  threaded    obj;
  bool        running;
  timeserver  time;
  serverinput keyboard;
}