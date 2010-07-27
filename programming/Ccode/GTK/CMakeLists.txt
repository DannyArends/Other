cmake_minimum_required(VERSION 2.6)
SET(EXECNAME GTK)

SET(PROJECT_INCLUDE_DIR "${PROJECT_INCLUDE_DIR}" "C:/GTK/include/gtk-2.0" "C:/GTK/include/gtk-2.0/include" "C:/GTK/include/atk-1.0" "C:/GTK/include/cairo" "C:/GTK/include/pango-1.0")
SET(PROJECT_INCLUDE_DIR "${PROJECT_INCLUDE_DIR}" "C:/GTK/include/fontconfig" "C:/GTK/include/freetype2" "C:/GTK/include/gail-1.0" "C:/GTK/include/glib-2.0" "C:/GTK/include/glib-2.0/include")
SET(PROJECT_INCLUDE_DIR "${PROJECT_INCLUDE_DIR}" "C:/GTK/include/libpng14" "C:/GTK/include" "C:/GTK/lib/gtk-2.0/include" "C:/GTK/lib/glib-2.0/include")

SET(PROJECT_LINK_DIR "${PROJECT_LINK_DIR}" "c:/GTK/lib")

SET(PROJECT_LINK_LIBS "${PROJECT_LINK_LIBS}" gtk-win32-2.0 gdk-win32-2.0 atk-1.0 gio-2.0 gdk_pixbuf-2.0 pangowin32-1.0 gdi32 pangocairo-1.0 pango-1.0 cairo gobject-2.0 gmodule-2.0 gthread-2.0 glib-2.0 intl)

INCLUDE_DIRECTORIES(${PROJECT_INCLUDE_DIR})
LINK_DIRECTORIES(${PROJECT_LINK_DIR})

ADD_DEFINITIONS(-mms-bitfields)

add_executable (${EXECNAME} 
main.cpp
)

TARGET_LINK_LIBRARIES(${EXECNAME} ${PROJECT_LINK_LIBS})

ENABLE_TESTING()
SET(EXECUTABLE "${EXECNAME}.exe")
ADD_TEST(Startup ${EXECUTABLE})
