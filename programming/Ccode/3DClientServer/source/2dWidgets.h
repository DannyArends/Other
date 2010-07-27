#ifndef __2DWIDGETS_H__
#define __2DWIDGETS_H__
#include "includes.h"
#include "DataStructures.h"
#include "OpenGL.h"

void create_window(window_type* win,int id,int x,int y,bool visible,char* name,char* texturename);
int windowlength(window_type window);
int windowwidth(window_type window);
void draw_window(window_type window, ApplicationInfo app);

button_type create_button(int x,int y, char* name, char* command, char* texturename);
void draw_btn(window_type curwin, button_type btn, ApplicationInfo app);
void disable_buttons(int winid,int btnid, hud_type* hud);
bool add_button(window_type* win, button_type btn);
bool add_text(window_type* win,const char* text);
bool add_window(hud_type* hud, window_type win);

void draw_fps(int width, ApplicationInfo app);
void draw_userinput(int height, ApplicationInfo app);

void c_func1(int winid,int btnid, hud_type* hud);
void c_func2(int winid,int btnid, hud_type* hud);
void c_func3(int winid,int btnid, hud_type* hud);
void c_func4(int winid,int btnid, hud_type* hud);
void c_func5(int winid,int btnid, hud_type* hud);
void c_func6(int winid,int btnid, hud_type* hud);
void c_func7(int winid,int btnid, hud_type* hud);

#endif
