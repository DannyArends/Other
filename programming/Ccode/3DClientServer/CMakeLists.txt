cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES("./source" "c:/SDL/include" "C:/Program Files/R/R-2.9.1/include")
LINK_DIRECTORIES("c:/SDL/bin" "c:/SDL/lib" "C:/Program Files/R/R-2.9.1/bin")
SET(EXECNAME prog)

FIND_PACKAGE( SDL REQUIRED )

link_libraries (
  R
  SDLmain
  SDL
  SDL_net
  Opengl32
)

add_executable (${EXECNAME} 
./source/DataStructures.cpp
./source/Error.cpp
./source/OpenGL.cpp
./source/2dWidgets.cpp
./source/3dWidgets.cpp
./source/2dWindow.cpp
./source/Handlers.cpp
./source/3dsSupport.cpp
./source/MAPLoader.cpp
./source/SDLcommon.cpp
./source/TGALoader.cpp
./source/FileIO.cpp
main.cpp
)

ENABLE_TESTING()
SET(EXECUTABLE "${EXECNAME}.exe")
ADD_TEST(Startup ${EXECUTABLE})
