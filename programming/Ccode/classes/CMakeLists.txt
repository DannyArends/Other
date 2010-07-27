cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES("./source" "c:/Pthreads/include" "c:/SDL/include")
LINK_DIRECTORIES("c:/SDL/bin" "c:/SDL/lib" "c:/Pthreads/lib" )
SET(EXECNAME prog)

link_libraries (
  pthreadGC2
  SDLmain
  SDL
  SDL_net
  Opengl32
)

add_executable (${EXECNAME} 
./source/error.cpp
./source/myapplication.cpp
./source/sdlcommon.cpp
./source/myhttpserver.cpp
main.cpp
)

ENABLE_TESTING()
SET(EXECUTABLE "${EXECNAME}.exe")
ADD_TEST(Startup ${EXECUTABLE})
