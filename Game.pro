TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -ftree-vectorize -pipe -Wall -Wextra -Wformat=2 -g
}

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -fasynchronous-unwind-tables -Wl,-z,relro -Wl,-z,now -O2 -ftree-vectorize -pipe -Wl,-z,defs -flto -fallocation-dce -Wl,-O1 -Wl,--no-undefined
}

HEADERS += \
    engine/animations/parallax.h \
    engine/enums/movedirection.h \
    engine/managers/statemanager.h \
    engine/managers/assetmanager.h \
    engine/enums/textalignment.h \
    engine/menus/textmenu.h \
    engine/interfaces/istate.h \
    engine/types/menuoptions.h \
    game/states/mainmenustate.h \
    game/states/splashstate.h \
    game/types/gamedata.h \
    game/definitions.h

SOURCES += \
        engine/menus/textmenu.cpp \
        game/states/mainmenustate.cpp \
        game/states/splashstate.cpp \
        main.cpp

DISTFILES += \

INCLUDEPATH += /usr/include/SFML
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window

LIBS += -lfmt -lX11

