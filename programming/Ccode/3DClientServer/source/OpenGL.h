#ifndef __OPENGL_H__
#define __OPENGL_H__
#include "includes.h"
#include "DataStructures.h"
#include "TGALoader.h"
#include "Error.h"
#include "OpenGL.h"
#include "FileIO.h"
#include "3dsSupport.h"
#include "3dWidgets.h"
#include "2dWindow.h"

bool init_3Dopengl(const int window_w, const int window_h);
bool IsExtensionSupported(char* szTargetExtension );
void render_scene(ApplicationInfo app,const int width, const int height);
#endif
