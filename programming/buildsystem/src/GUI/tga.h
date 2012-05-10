/**
 * \file GUI/tga.h
 * \brief Header file, for GUI/tga.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/
 
#ifndef TGA_H_
  #define TGA_H_
  #include "GUI.h"
  
  enum TgaType { TGA_ERROR_FILE_OPEN = -5, TGA_ERROR_READING_FILE = -4, TGA_ERROR_INDEXED_COLOR = -3, TGA_ERROR_MEMORY = -2, TGA_ERROR_COMPRESSED_FILE = -1, TGA_OK = 0};

  tgaInfo*  tgaLoad(const char* filename);
  int       tgaSave(const char* filename, short int width, short int height, unsigned char pixelDepth, unsigned char *imageData);
  int       tgaSaveSeries(char* filename, short int width, short int height, unsigned char pixelDepth, unsigned char *imageData);
  void      tgaRGBtoGreyscale(tgaInfo* info);
  int       tgaGrabScreenSeries(char* filename, int x,int y, int w, int h);
  void      tgaDestroy(tgaInfo* info);
#endif
