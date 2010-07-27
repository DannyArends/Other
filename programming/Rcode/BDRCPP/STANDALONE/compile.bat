set PATH=C:\Program Files\Git\cmd;C:\Program Files\CMake 2.6\bin;C:\Rtools\mingw\bin;C:\Rtools\perl\bin;C:\mingw\bin;C:\Program Files\R\R-2.9.1\bin;"C:\PThread\include"
del CMakeCache.txt
cmake -G "MinGW Makefiles" .
mingw32-make.exe clean
mingw32-make.exe
mingw32-make.exe test