#ifndef __2DWINDOW_H__
#define __2DWINDOW_H__
#include "includes.h"
#include "DataStructures.h"
#include "OpenGL.h"
#include "2dWidgets.h"

typedef struct function_entry {
       char name[32];
       void (*address)(int,int,hud_type*);
}function_entry;

void setup_hud_new(hud_type* hud);
bool check_for_button(int x, int y, hud_type* hud);
void render_hud(int width,int height, ApplicationInfo app);

#endif
