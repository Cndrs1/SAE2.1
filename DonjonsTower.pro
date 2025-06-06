QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    boss.cpp \
    donjon.cpp \
    door.cpp \
    enemy.cpp \
    game.cpp \
    item.cpp \
    key.cpp \
    main.cpp \
    gui.cpp \
    menuwidget.cpp \
    player.cpp \
    room.cpp \
    scores.cpp \
    trap.cpp

HEADERS += \
    arrow.h \
    boss.h \
    direction.h \
    donjon.h \
    door.h \
    enemy.h \
    game.h \
    gui.h \
    item.h \
    key.h \
    menuwidget.h \
    player.h \
    room.h \
    scores.h \
    trap.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Font.qrc \
    Map.qrc \
    Sprite.qrc
