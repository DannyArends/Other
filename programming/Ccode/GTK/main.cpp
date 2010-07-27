#include <gtk/gtk.h>
#define UI_FILE "my.glade" 
 
#define CH_GET_OBJECT( builder, name, type, data ) \
data->name = type( gtk_builder_get_object( builder, #name ) )
#define CH_GET_WIDGET( builder, name, data ) \
CH_GET_OBJECT( builder, name, GTK_WIDGET, data )

 
struct Interface{
  GtkWidget *mainwindow;          /* Main application window */
  GtkWidget *menubar;             /* Main maenubar */
  GtkWidget *filequit;            /* Main maenubar */
  GtkWidget *statusbar;           /* Main statusbar */
  GtkWidget *sidearea;            /* Main sidearea */
  GtkWidget *drawwindow;          /* Main drawwindow */
}; 

void callbackhandler(GtkWidget *origin, gpointer data){ 
  printf("Event: %s\n",(char*) data);
  gtk_main_quit();
}
 
 
 int init_gtk(int argc, char *argv[]){
  GtkBuilder  *builder; 
  GtkWidget   *label;
  Interface   *data; 
  GError      *error = NULL;
  
  gtk_init (&argc, &argv);
  builder = gtk_builder_new(); 
  if(!gtk_builder_add_from_file( builder, UI_FILE, &error )){ 
    g_warning("%s", error->message); 
    g_free(error); 
    return(1); 
  } 
  data = g_slice_new(Interface);
  
  /* Get objects from UI */
  #define GW(name) CH_GET_WIDGET(builder, name, data) 
      GW( mainwindow ); 
      GW( menubar ); 
      GW( filequit ); 
      GW( statusbar );
      GW( sidearea );
      GW( drawwindow );
  #undef GW 
  
  gtk_builder_connect_signals(builder, data); 
  g_object_unref(G_OBJECT(builder)); 
  g_signal_connect(data->mainwindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(data->filequit, "activate", G_CALLBACK(callbackhandler), (void*)"Test");
  
  gtk_window_set_title (GTK_WINDOW(data->mainwindow), "Testing GTK iterface for C/C++ v0.0.1");
  gtk_window_set_position(GTK_WINDOW(data->mainwindow), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(GTK_WINDOW(data->mainwindow), false);
  gtk_widget_show(data->mainwindow); 

  gtk_main();
  g_slice_free(Interface, data); 
  return 0;
 }
