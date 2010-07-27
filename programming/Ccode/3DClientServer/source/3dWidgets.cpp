#include "3dWidgets.h"

void rendermap(ApplicationInfo application){
  glCallList(application.maps[application.c_map].DisplayList);
}

