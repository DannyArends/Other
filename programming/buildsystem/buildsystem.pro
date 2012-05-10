CONFIG = debug

INCLUDEPATH = ./src ./external/src 

LIBS = -L./external/bin -lsqlite3 -lpthreadGC2 -lSDL -lSDL_net -lopengl32 -lglu32

OBJECTS_DIR = ./debug

DESTDIR = ./

PRECOMPILED_HEADER  = src/includes.h

HEADERS += src/main.h \
    src/includes.h \
    src/config.h \
    src/basicincludes.h \
    src/application.h \
    src/BASE/tree.h \
    src/BASE/object.h \
    src/BASE/myio.h \
    src/BASE/lsystem.h \
    src/BASE/keyboard.h \
    src/BASE/datatypes.h \
    src/BASE/database.h \
    src/BASE/configfile.h \
    src/BASE/BASEstructures.h \
    src/BASE/BASE.h \
    src/GAME/world.h \
    src/GAME/user.h \
    src/GAME/storyline.h \
    src/GAME/storage.h \
    src/GAME/npc.h \
    src/GAME/item.h \
    src/GAME/GAMEstructures.h \
    src/GAME/gameevent.h \
    src/GAME/gameengine.h \
    src/GAME/GAME.h \
    src/GUI/universe.h \
    src/GUI/tga.h \
    src/GUI/screenhandler.h \
    src/GUI/hud.h \
    src/GUI/GUI.h \
    src/GUI/engine.h \
    src/GUI/camera.h \
    src/MYMATH/regression.h \
    src/MYMATH/population.h \
    src/MYMATH/pathfinding.h \
    src/MYMATH/MYMATH.h \
    src/MYMATH/geneticalgorithm.h \
    src/MYMATH/curve.h \
    src/MYMATH/compartiment.h \
    src/MYMATH/biology.h \
    src/NETWORK/sdlserver.h \
    src/NETWORK/sdlclient.h \
    src/NETWORK/protocol.h \
    src/NETWORK/NETWORK.h \
    src/NETWORK/httpserver.h \
    src/NETWORK/cloudmember.h \
    src/THREADING/timeserver.h \
    src/THREADING/THREADING.h \
    src/GUI/entities/turtle.h \
    src/GUI/entities/terrain.h \
    src/GUI/entities/sphere.h \
    src/GUI/entities/skeleton.h \
    src/GUI/entities/particle.h \
    src/GUI/entities/object3ds.h \
    src/GUI/entities/normals.h \
    src/GUI/entities/line.h \
    src/GUI/entities/force.h \
    src/GUI/entities/ENTITIES.h \
    src/GUI/entities/emitter.h \
    src/GUI/entities/bone.h \
    src/GUI/widgets/window.h \
    src/GUI/widgets/WIDGETS.h \
    src/GUI/widgets/widgetfactory.h \
    src/GUI/widgets/timeclock.h \
    src/GUI/widgets/text.h \
    src/GUI/widgets/square.h \
    src/GUI/widgets/mainmenu.h \
    src/GUI/widgets/inputbox.h \
    src/GUI/widgets/button.h \
    src/MYMATH/astar/stlastar.h \
    src/MYMATH/astar/fsa.h \
    src/includes.h \
    src/config.h \
    src/basicincludes.h \
    src/application.h \
    src/main.h
SOURCES += src/main.cpp \
    src/BASE/tree.cpp \
    src/BASE/object.cpp \
    src/BASE/myio.cpp \
    src/BASE/lsystem.cpp \
    src/BASE/keyboard.cpp \
    src/BASE/datatypes.cpp \
    src/BASE/database.cpp \
    src/BASE/configfile.cpp \
    src/GAME/world.cpp \
    src/GAME/user.cpp \
    src/GAME/storyline.cpp \
    src/GAME/storage.cpp \
    src/GAME/npc.cpp \
    src/GAME/item.cpp \
    src/GAME/gameevent.cpp \
    src/GAME/gameengine.cpp \
    src/GUI/universe.cpp \
    src/GUI/tga.cpp \
    src/GUI/screenhandler.cpp \
    src/GUI/hud.cpp \
    src/GUI/engine.cpp \
    src/GUI/camera.cpp \
    src/MYMATH/regression.cpp \
    src/MYMATH/population.cpp \
    src/MYMATH/pathfinding.cpp \
    src/MYMATH/geneticalgorithm.cpp \
    src/MYMATH/curve.cpp \
    src/MYMATH/compartiment.cpp \
    src/MYMATH/biology.cpp \
    src/NETWORK/sdlserver.cpp \
    src/NETWORK/sdlclient.cpp \
    src/NETWORK/protocol.cpp \
    src/NETWORK/httpserver.cpp \
    src/NETWORK/cloudmember.cpp \
    src/THREADING/timeserver.cpp \
    src/THREADING/mythread.cpp \
    src/GUI/entities/turtle.cpp \
    src/GUI/entities/terrain.cpp \
    src/GUI/entities/sphere.cpp \
    src/GUI/entities/skeleton.cpp \
    src/GUI/entities/particle.cpp \
    src/GUI/entities/object3ds.cpp \
    src/GUI/entities/normals.cpp \
    src/GUI/entities/line.cpp \
    src/GUI/entities/force.cpp \
    src/GUI/entities/entity.cpp \
    src/GUI/entities/emitter.cpp \
    src/GUI/entities/bone.cpp \
    src/GUI/widgets/window.cpp \
    src/GUI/widgets/widgetfactory.cpp \
    src/GUI/widgets/widget.cpp \
    src/GUI/widgets/timeclock.cpp \
    src/GUI/widgets/text.cpp \
    src/GUI/widgets/square.cpp \
    src/GUI/widgets/mainmenu.cpp \
    src/GUI/widgets/inputbox.cpp \
    src/GUI/widgets/button.cpp \
