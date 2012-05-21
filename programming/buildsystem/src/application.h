/**
* \file application.h
* \brief File holding the main application class.<br>
*
* TODO Description<br>
* bugs: none found<br>
*/
#ifndef APPLICATION_H_
  #define APPLICATION_H_

  struct sdlserverstruct;
  class timeserver;
  class sdlserver;
  class httpserver;
  class cloudmember;
  class engine;

  /**
  * \brief Application class serving mayor components to each other<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class application : public object{
    public:
                        application();
      configfile*       getconfigurationfile(void);
      myio*             getfilesystem(void);
      sdlserverstruct*  getsdlserverstruct(void);
      database*         getdatabase(void);
      sdlserver*        getsdlserver(void);
      httpserver*       gethttpserver(void);
      cloudmember*      getcloudmember(void);
      engine*           getgui(void);
      void              setgui(engine* guiengine);

    private:
    configfile*         myconfigfile;
    sdlserverstruct*    information;
    timeserver*         time;
    database*           db;
    sdlserver*          sdl;
    httpserver*         http;
    engine*             gui;
    myio*               filesystem;
  };

#endif

