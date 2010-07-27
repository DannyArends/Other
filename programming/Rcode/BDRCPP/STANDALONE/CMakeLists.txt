cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES("../src" "C:/Program Files/R/R-2.9.1/include" "C:/PThread/include")
LINK_DIRECTORIES("C:/Program Files/R/R-2.9.1/bin" "C:/PThread/lib" "C:/Rtools/MinGW/lib")
SET(EXECNAME rggQTL)

SET (CMAKE_MODULE_LINKER_FLAGS -fopenmp)

link_libraries (
  R
)

add_executable (${EXECNAME}
../src/includes.cpp
../src/interface.cpp
main.cpp
)

ENABLE_TESTING()
SET(EXECUTABLE "${EXECNAME}.exe")
ADD_TEST(startandhelp ${EXECUTABLE} -h)
