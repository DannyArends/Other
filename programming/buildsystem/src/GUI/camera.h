/**
 * \file GUI/camera.h
 * \brief Header file, for GUI/camera.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef CAMERA_H_
  #define CAMERA_H_
  #include "GUI.h"

  /**
  * \brief Class holding objects in the universe
  *
  * TODO Description<br>
  * bugs: none found
  */
  class camera : public object3d{
    public:
      camera();
      void follow(entity* target);
      void update(uint life);
      void setrotation(float x,float y,float z);
      float getrotation(uint index);
      ~camera();
    private:
      GLfloat  rotation[3];
      entity*  target;
      float    distancetotarget;
      bool     followmode;
  };

#endif /* CAMERA_H_ */
