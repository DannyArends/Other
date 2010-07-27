#include "2dWindow.h"


void create_menu(hud_type* hud){
  window_type* temp = new window_type;
  create_window(temp,0,5,30,true,(char *)"Main",(char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"File",    (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,30,(char *)"User",   (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,60,(char *)"Server", (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,90,(char *)"Options",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,120,(char *)"Help",  (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_window(hud,*temp);
  create_window(temp,1,125,30,false,(char *)"File",    (char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"New User",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,30,(char *)"Login",  (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,60,(char *)"Quit",   (char *)"EXIT",(char *)"BTN1.tga"));
  add_window(hud,*temp);
  create_window(temp,2,125,60,false,(char *)"User",     (char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"Inventory",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,30,(char *)"Stats",   (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,60,(char *)"Storage", (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_window(hud,*temp);
  create_window(temp,3,125,90,false,(char *)"Server",       (char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"Start/Stop",   (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,30,(char *)"ServerStats", (char *)"WINOPEN",(char *)"BTN1.tga"));  
  add_button(temp,create_button(0,60,(char *)"Connect",     (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,90,(char *)"Objecteditor",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,120,(char *)"Mapeditor",  (char *)"WINOPEN",(char *)"BTN1.tga"));
  add_window(hud,*temp);  
  create_window(temp,4,125,120,false,(char *)"Options",(char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"Controls",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_button(temp,create_button(0,30,(char *)"Graphics",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_window(hud,*temp);  
  create_window(temp,5,125,150,false,(char *)"Help",(char *)"TestBack.tga");
  add_button(temp,create_button(0,0,(char *)"About",(char *)"WINOPEN",(char *)"BTN1.tga"));
  add_window(hud,*temp);  
  create_window(temp,6,350,200,false,(char *)"About",(char *)"TestBack.tga");
  add_text(temp,(const char *)"Created by Danny Arends");
  add_text(temp,(const char *)"       (c) 2009        ");
  add_window(hud,*temp);
}

void setup_hud_new(hud_type* hud){
  for(int x=0;x<MAX_CHAR;x++){
    hud->textinput[x] = ' ';
  }
  hud->cur_char=0;
  create_menu(hud);
}

function_entry symtab[] = {
         {"OK",       c_func1},
         {"CANCEL",   c_func2},
         {"NEXT",     c_func3},
         {"BACK",     c_func4}, 
         {"WINOPEN",  c_func5},         
         {"WINCLOSE", c_func6},
         {"EXIT",     c_func7},         
};

bool check_for_button(int x, int y,hud_type* hud){
  window_type curwin;
  for(int win = 0;win< hud->num_windows;win++){
    curwin = hud->windows[win];
    if(curwin.on){
      for(int btn = 0;btn< curwin.num_buttons;btn++){
        int btnx = curwin.x+curwin.buttons[btn].x;
        int btny = (curwin.y+curwin.buttons[btn].y);
        int btnl = (curwin.buttons[btn].l*13)+6;
        if(x >= btnx && x <= btnx+btnl && y<= btny+20 && y>= btny){
          for (unsigned int i = 0; i < sizeof symtab / sizeof symtab[0]; i++) {
            if (strcmp(curwin.buttons[btn].on_click, symtab[i].name) == 0) {
              symtab[i].address(curwin.winid,btn,hud);
              return true;
            }
          }
          printf("this button has unknonw on_click: %s\n",curwin.buttons[btn].on_click);
          return false;
        }
      }
    }
  }
  return false;
}

void render_hud(int width,int height, ApplicationInfo app){
  for(int x = 0;x< app.hud.num_windows;x++){
    if(app.hud.windows[x].on) draw_window(app.hud.windows[x],app);
  }
  draw_fps(width,app);        //Draw last
  draw_userinput(height,app);  //So visible
}


