#include "Handlers.h"

/*
void setup_hud(ApplicationInfo* app){
  for(int x=0;x<MAX_CHAR;x++){
    app->hud.textinput[x] = ' ';
  }
  app->hud.cur_char=0;
}*/

void setup_camera(camera_type* camera){
  camera->x = 0.0f;
  camera->y = 0.0f;
  camera->z = 0.0f;
  camera->angle_h = 0;
  camera->angle_v = 0;
  camera->locked=false;
}

void rotate_camera(camera_type* camera,const int direction,const int side){
	if(direction > 0){
		if(side){
		camera->angle_v = int(camera->angle_v + 2) % 360;
		}else{
		camera->angle_h= int(camera->angle_h + 2) % 360;
		}
	}
	if(direction < 0){
		if(side){
		camera->angle_v = int(camera->angle_v - 2) % 360;
		}else{
		camera->angle_h = int(camera->angle_h - 2) % 360;
		}
	}
}

void move_camera(camera_type* camera,int x, int y, int z){
	camera->x = camera->x + float(sin((camera->angle_h*PI)/180)*x/10.0f);
	camera->y += y/2.0f;
	camera->z = camera->z - float(cos((camera->angle_h*PI)/180)*z/10.0f);
}

bool check_movement(ApplicationInfo* app, Uint8* keystate){
  //movement keys
  if ( keystate[SDLK_RIGHT]){rotate_camera(&app->camera,1,0); return true;}
  if ( keystate[SDLK_LEFT]) {rotate_camera(&app->camera,-1,0); return true;}
  if ( keystate[SDLK_UP])   {move_camera(&app->camera,-5,0,-5); return true;}
  if ( keystate[SDLK_DOWN]) {move_camera(&app->camera,5,0,5); return true;}
  if ( keystate[SDLK_PAGEUP]) {move_camera(&app->camera,0,-1,0); return true;}
  if ( keystate[SDLK_PAGEDOWN]) {move_camera(&app->camera,0,1,0); return true;}
  return false;
}

void check_keydown(ApplicationInfo* app,SDL_Event event, Uint8* keystate){
 
  //Special for text
  if ( keystate[SDLK_RETURN] ) {
    for(int x=0;x<app->hud.cur_char;x++){
      app->hud.textinput[x] = ' ';
    }
    app->hud.cur_char=0;
    printf("Enter pressed.\n");
    return;
  }
  
  if ( keystate[SDLK_BACKSPACE]){
    if(app->hud.cur_char>=0){
      app->hud.textinput[app->hud.cur_char] = ' ';
      app->hud.cur_char > 0 ? app->hud.cur_char-- : 0;
      printf("Clear.\n");
    }
    return;
  }
  if ( keystate[SDLK_DELETE]){ printf("Delete.\n");return;}
  if(app->hud.cur_char < MAX_CHAR){
    app->hud.textinput[app->hud.cur_char] = (char)event.key.keysym.sym;
    app->hud.cur_char++;
  }
}



