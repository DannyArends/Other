/**
 * \file BASE/BASEstructures.h
 * \brief Header file, for the BASE directory
 *
 * This class is used to share the objects within the BASE directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef BASESTRUCTURES_H_
  #define BASESTRUCTURES_H_
  #include "includes.h"

  /**
   * \brief Enumerator of known buffer sizes
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum buffersizes { BUFFER16 = 16, NAMESIZE = 20, BUFFER32 = 32, BUFFER64 = 64, BUFFER256 = 256, BUFFER1024 = 1024, BUFFER1MB = BUFFER1024*BUFFER1024 };

  /**
   * \brief Enumerator of known file types
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum filetypes { MYFILE = 'F', MYDIR = 'D', BINARYFILE = 'B', TEXTUREFILE = 'T', MAPFILE = 'M', USERFILE = 'U', OBJECTFILE = 'O' };

  /**
   * \brief Enumerator of known basic types
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum basictypes { MYINTEGER = 'I', MYFLOAT = 'F', MYDOUBLE = 'D', MYSTRING = 'S', MYPATH = 'P' };

  /**
   * \brief Structure defining a parameter in \ref basictypes
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct param{
    basictypes  t;
    string    value;
  }param;

  /**
   * \brief Structure defining RGB color in 4 floats 0..1 (R,G,B,Alpha)
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct RGBcolor{
    float r,g,b;
    float alpha;
  }RGBcolor;

  const RGBcolor RED      ={1.0f,0.0f,0.0f,1.0f};
  const RGBcolor GREEN    ={0.0f,1.0f,0.0f,1.0f};
  const RGBcolor BLUE     ={0.0f,0.0f,1.0f,1.0f};
  const RGBcolor YELLOW   ={1.0f,1.0f,0.0f,1.0f};
  const RGBcolor WHITE    ={1.0f,1.0f,1.0f,1.0f};
  const RGBcolor GRAY70   ={0.7f,0.7f,0.7f,1.0f};
  const RGBcolor GRAY     ={0.5f,0.5f,0.5f,1.0f};
  const RGBcolor GRAY20   ={0.2f,0.2f,0.2f,1.0f};
  const RGBcolor BLACK    ={0.0f,0.0f,0.0f,1.0f};

  /**
   * \brief Structure defining a setting (name=value)
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct setting{
    string    name;
    param     p;
  }setting;

  /**
   * \brief Structure holding IO file objects
   *
   * TODO Description & name change<br>
   * bugs: none found<br>
   */
  typedef struct permanentdata{
    string    path;
    char      name[NAMESIZE];
    filetypes  type;
  }permanentdata;

  /**
   * \brief Structure monitoring keyboard input in the terminal
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  typedef struct keyboardinput{
    bool        running;
    char*       command;
  }keyboardinput;

  typedef double**  dmatrix;
  typedef double*   dvector;
  typedef bool*     bvector;
  typedef char**    cmatrix;
  typedef char*     cvector;
  typedef int**     imatrix;
  typedef int*      ivector;

#endif
