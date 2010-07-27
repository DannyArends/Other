set PATH=C:\Program Files\Git\cmd;C:\Program Files\CMake 2.6\bin;C:\MINGW\BIN;C:\Ruby\bin;C:\Program Files\MiKTeX 2.7\miktex\bin;C:\Perl\bin;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;C:\Program Files\Microsoft SQL Server\90\Tools\binn\;C:\Program Files\R\R-2.7.0\bin;C:\Program Files\VDMSound;C:\Program Files\HTML Help Workshop;D:\Appz\Visual Studio\VC\bin;C:\Program Files\R\R-2.9.1;C:\Program Files\R\R-2.9.1\bin;C:/PROGRA~1/R/R-29~1.1\bin;C:/PROGRA~1/R/R-29~1.1\lib;C:\Program Files\Mono-2.4.2.2\bin
del CMakeCache.txt
cmake -G "MinGW Makefiles" .
mingw32-make.exe clean
mingw32-make.exe
mingw32-make.exe test
