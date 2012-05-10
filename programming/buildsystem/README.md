The BUILDSYSTEM
=================
Welcome to the Buildsystem, this project is hard to describe in a single world, so lets not try to do that.

Dependencies
------------
For running buildsystem some requirements have to be met these are:

- [Win32](http://www.microsoft.com/ "Microsoft") / Unix
- [QT](http://qt.nokia.com/ "QT") or [Eclipse](http://www.eclipse.org/ "Eclipse"), [Eclipse CDT perspective](http://www.eclipse.org/cdt/ "C/C++ Development Tooling")
- [Minimal GNU for Windows](http://www.mingw.org/ "MinGW") : C and C++ compiler, or unix variants
- (Provided:) SDL, pthreads, SDL_net, sqlite3 (provided in: [external](http://github.com/DannyArends/buildsystem/tree/master/external/ "External Includes and Libraries"))

Installation
------------

Step 0: Setup dependencies

- Install Eclipse + CDT builder
- Optional (but recommended):  [Doxygen Plugin](http://download.gna.org/eclox/update/ "EclOx Plugin") for eclipse
- Optional (but recommended):  [Git Plugin](http://www.eclipse.org/egit/ "EGIT") for eclipse

Step 1: Installing the project into with eclipse

- (Optional) Create a new workspace 
- Open the c++ perspective in eclipse
- (Win32) Create a new empty c++ application (MinGW toolchain)
- (UNIX) Create a new empty c++ application (Linux/GCC toolchain)
- Extract the contents from the .zip file or clone buildsystem.git
- Refresh the workspace / buildsystem c++ application (to show the extracted files)

Step 1a: Setup dependencies yourself

- Add to the C++ and C compiler include directory: %project%/external/src, %project%/src
- (Win32) Add to the Linker libraries include directory: %project%/external/bin
- (Win32) Add to the Linker libraries: pthreadGC2,SDL,SDL_Net,sqlite3,OpenGL32,Glu32
- (UNIX) Install the following libs: libgl1-mesa-dev, libglu1-mesa-dev, libsdl1.2-dev, libsdl-net1.2-dev, sqlite3, sqlite3-dev
- (UNIX) Add to the Linker libraries: pthread,SDL,SDL_net,sqlite3,GL,GLU

Step 1b: Use the dependencies file

- Close Eclipse ;)
- Delete the eclipse generated .cproject file
- (Win32) Copy the /external/eclipse.cprojectWIN32 as .cproject in the project directory in the eclipse workspace directory 
- (UNIX) Copy the /external/eclipse.cprojectUNIX as .cproject in the project directory in the eclipse workspace directory
- Restart Eclipse ;)   

Step 2: Executing the application

- Press the run button
- (Win32) If nothing happens (no text in console), Open the Run Configuration -> Environment of the project
- (Win32) Add a new variable called 'Path' and add as value: c:/minGW/bin;%project%/external/bin 

What is it ?
------------

Well its a collection of random code i produced during my life, documented and put online for people to learn from and perhaps use.

TODO
----

Remove dependencies we have or get them from an online repository system or such, furthermore:

- Finish off networking code
- Speed up compilation
- Game world creator with map-format
- Fix all the TODOs already present in code
- Subdivide the project and distribute an entire workspace ?

Contributing
------------

Want to contribute? Great!

1. Clone it.
2. Compile it.
3. Run it.
4. Modify some code. (Search -> 'TODO')
5. Go back to 2, or
6. Submit a patch

You can also just post comments on code / commits.

Danny Arends

Disclaimer
----------
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 3, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  See the GNU
General Public License, version 3, for more details.

A copy of the GNU General Public License, version 3, is available
at [http://www.r-project.org/Licenses/GPL-3](http://www.r-project.org/Licenses/GPL-3 "GPL-3 Licence")
Copyright (c) 2010 Danny Arends
