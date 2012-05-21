/**
 * \file GUI/widgets/timeclock.h
 * \brief Header file, for GUI/widgets/timeclock.cpp
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef TIMECLOCK_H_
  #define TIMECLOCK_H_

  #include "WIDGETS.h"

  /**
   * \brief Widget displaying times at all attached servers<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class timeclock: public widget, public taskholder{
    public:
      timeclock();
      timeclock(hud* huddisplay);
      void settime(string line);
      virtual void runtask(void); // Default task: sending ping to servers
      ~timeclock(void);
      void render(void);
    private:
      void init();
  };

#endif /* TIMECLOCK_H_ */
