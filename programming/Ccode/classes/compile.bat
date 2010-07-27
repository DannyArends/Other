set PATH=C:\Program Files\Git\cmd;C:\Program Files\CMake 2.6\bin;C:\MinGW\bin;C:\Pthreads\lib;c:\SDL\bin
del CMakeCache.txt
cmake -G "MinGW Makefiles" .
mingw32-make.exe clean
mingw32-make.exe
mingw32-make.exe test