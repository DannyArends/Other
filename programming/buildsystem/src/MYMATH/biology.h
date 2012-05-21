/**
 * \file MYMATH/biology.h
 * \brief Header file, for MYMATH/biology.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef BIOLOGY_H_
  #define BIOLOGY_H_
  
  #include "MYMATH.h"
   
   enum basetype{ DNA=0, RNA=1 };
   enum basevalue{ A=0, C=1, T=2, G=3, U=4 };
   
   class basepair;

 /**
  * \brief base class representing 1 base<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class base : public mathobject{
    public:
      base();
      base(basetype type,basevalue base);
      ~base();
      basepair* getbasepair(void);
      basetype  is(void);
    private:
      basetype type;
      basevalue  value;
  };
  
  /**
   * \brief basepair class representing 1 basepair<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class basepair : public mathobject{
    public:
      basepair();
      ~basepair();
    private:
      base* five;
      base* three;
  };
  
  /**
   * \brief single linear strand class representing 1 linear strand<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class singlestrand : public mathobject{
    public:
      singlestrand();
      ~singlestrand();
    private:
    vector<base*> strand;
  };
  
  /**
   * \brief double linear strand class representing 1 double strand<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class doublestrand : public mathobject{
    public:
      doublestrand();
      ~doublestrand();
    private:
    vector<basepair*> strand;
  };

#endif
