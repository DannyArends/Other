#include "2dWidgets.h"

GLvoid glPrint2D(GLint x, GLint y, ApplicationInfo app, const char *message, ...){
  //Print to openGL window
	if (message == NULL){										  // If There's No Text
		return;												          // Do Nothing
  }
	char		text[1024];									      // Holds Our String
	va_list		ap;											        // Pointer To List Of Arguments
	va_start(ap, message);										// Parses The String For Variables
	vsprintf(text, message, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);												        // Results Are Stored In Text
	glEnable(GL_TEXTURE_2D);								                            // Enable Texture Mapping
  glBindTexture (GL_TEXTURE_2D, app.textures[app.font_texture].texID);
  glPushMatrix();
	glLoadIdentity();										                                // Reset The Modelview Matrix
	glTranslated(x,y,0);									                              // Position The Text (0,0 - Top Left)
	glListBase(app.textures[app.font_texture].base-32);							    // Choose The Font Set (0 or 1)
	glScalef(0.9f,0.9f,1.0f);								                            // Make The Text 2X Smaller
  glColor4f( 1.0f,  1.0f, 1.0f, 0.5f);
	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);		                // Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);								                            // Disable Texture Mapping
  glPopMatrix();
  //cleanup
  free((void*)text);
}

void draw_fps(int width, ApplicationInfo app){
  glPrint2D(width-100,10,app,"FPS:%d",app.fps);
}

void draw_userinput(int height, ApplicationInfo app){
  glPrint2D(10,height-20,app,"%s",app.hud.textinput);
}

void draw_btn(window_type curwin, button_type btn, ApplicationInfo app){
  int btnx = curwin.x+btn.x;
  int btny = (curwin.y+btn.y);
  int btnym = btny+20;
  int btnxl = btnx+(btn.l*13)+6;
  glPushMatrix();
  btn.on ? glColor4f( 0.0f,  0.0f, 0.7f, 0.5f) : glColor4f( 0.7f,  0.7f, 0.7f, 0.5f);
  glBegin( GL_QUADS );
    glVertex3f( btnx, btny, 0 );
    glVertex3f( btnxl, btny, 0 );
    glVertex3f( btnxl, btnym, 0 );
    glVertex3f( btnx, btnym, 0 );
  glEnd();
  glPopMatrix();
  glPrint2D(btnx+3, btny+3, app, btn.name);
}

int windowlength(window_type window){
  return window.num_buttons*30+window.num_lines*17;
}

int windowwidth(window_type window){
  int max = 0;
  for(int x = 0;x< window.num_lines;x++){
    if(strlen(window.lines[x])*13 > max){
      max = strlen(window.lines[x])*13; 
    }
  }
  for(int x = 0;x< window.num_buttons;x++){
    if(window.buttons[x].l*13+10 > max){
      max = window.buttons[x].l*13+10; 
    }
  }
  return max;
}

void draw_window(window_type window, ApplicationInfo app){
  glPushMatrix();
  glColor4f( 0.15f,  0.15f, 0.15f, 0.15f);
  glBegin( GL_QUADS );
    glVertex3f( window.x-4, window.y-4, 0 );
    glVertex3f( window.x+windowwidth(window), window.y-4, 0 );
    glVertex3f( window.x+windowwidth(window), window.y+windowlength(window), 0 );
    glVertex3f( window.x-4, window.y+windowlength(window), 0 );
  glEnd();
  glPopMatrix();
  for(int x = 0;x< window.num_lines;x++){
    glPrint2D(window.x, window.y+16*x, app, window.lines[x]);
  }
  for(int x = 0;x< window.num_buttons;x++){
    draw_btn(window,window.buttons[x],app);
  }
}

void c_func1(int winid,int btnid, hud_type* hud){
   printf("OK function by button: %d on window %d\n",btnid,winid);       
}

void c_func2(int winid,int btnid, hud_type* hud){
   printf("CANCEL function by button: %d on window %d\n",btnid,winid);       
}

void c_func3(int winid,int btnid, hud_type* hud){
   printf("NEXT function by button: %d on window %d\n",btnid,winid);       
}

void c_func4(int winid,int btnid, hud_type* hud){
   printf("BACK function by button: %d on window %d\n",btnid,winid);       
}

void disable_buttons(int winid,int btnid, hud_type* hud){
  for(int x = 0;x<hud->windows[winid].num_buttons;x++){
    if(x==btnid){
      hud->windows[winid].buttons[btnid].on ? hud->windows[winid].buttons[btnid].on=false : hud->windows[winid].buttons[btnid].on = true;
    }else{
      hud->windows[winid].buttons[x].on=false;
    }
  }
}

void c_func5(int winid,int btnid, hud_type* hud){
  disable_buttons( winid, btnid, hud);
  for(int win = 1;win< hud->num_windows;win++){
    if(strcmp(hud->windows[win].name,hud->windows[winid].buttons[btnid].name) == 0){
      hud->windows[win].on ?  hud->windows[win].on = false :  hud->windows[win].on = true;
    }else{
      if(winid!=win) hud->windows[win].on = false;
    }
  }
  printf("Request to open window %s from %d\n",hud->windows[winid].buttons[btnid].name,winid);       
}

void c_func6(int winid,int btnid, hud_type* hud){
  printf("Request to close window %d from %d\n",btnid,winid); 
  hud->windows[winid].on = false;
}

void c_func7(int winid,int btnid, hud_type* hud){
  printf("Request to Exit\n");
  exit(0);
}



button_type create_button(int x,int y, char* name, char* command, char* texturename){
  button_type newbtn;
  newbtn.on=false;
  newbtn.x=x;
  newbtn.y=y;
  newbtn.l=strlen(name);
  sprintf(newbtn.name,name);
  sprintf(newbtn.on_click,command);
  sprintf(newbtn.texturename,texturename);
  return newbtn;
}

void create_window(window_type* win,int id,int x,int y,bool visible,char* name,char* texturename){
  win->winid=id;
  win->x=x;
  win->y=y;
  win->xl=150;
  win->on=visible;
  sprintf(win->name,name);
  sprintf(win->texturename,texturename);
  win->num_buttons=0;
  win->num_lines=0;
  win->buttons = NULL;
}

bool add_button(window_type* win, button_type btn){
  button_type* newbtns;
  newbtns = (button_type *)calloc(win->num_buttons+1, sizeof(button_type));
  for(int x = 0;x<win->num_buttons;x++){
    newbtns[x] = win->buttons[x];
  }
  newbtns[win->num_buttons] = btn;
  win->buttons = newbtns;
  win->num_buttons++;
  return true;
}

bool add_text(window_type* win,const char* text){
  char** newtext;
  newtext = (char **)calloc(win->num_lines+1, sizeof(char*));
  for(int x = 0;x<win->num_lines;x++){
    newtext[x] = win->lines[x];
  }
  newtext[win->num_lines] = (char*)text;
  win->lines = newtext;
  win->num_lines++;
  return true;
}

bool add_window(hud_type* hud, window_type win){
  window_type* newwins;
  newwins = (window_type *)calloc(hud->num_windows+1, sizeof(window_type));
  for(int x = 0;x < hud->num_windows;x++){
    newwins[x] = hud->windows[x];
  }
  newwins[hud->num_windows] = win;
  hud->windows = newwins;
  hud->num_windows++;
  return true;
}
