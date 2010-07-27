#ifndef __HANDLERS_H__
#define __HANDLERS_H__
#include "includes.h"
#include "datastructures.h"
//void setup_hud(ApplicationInfo* app);
void setup_camera(camera_type* camera);
bool check_movement(ApplicationInfo* app, Uint8* keystate);
void check_keydown(ApplicationInfo* app,SDL_Event event, Uint8* keystate);

#endif
