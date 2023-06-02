QT       += core gui \
          multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    bullet.cpp \
    coins.cpp \
    door.cpp \
    enemy.cpp \
    enemy_2.cpp \
    health.cpp \
    heart.cpp \
    loggedinScreen.cpp \
    login.cpp \
    lostscreen.cpp \
    main.cpp \
    map.cpp \
    pausedscreen.cpp \
    player.cpp \
    signup.cpp \
    startingscreen.cpp \
    winningscreen.cpp

HEADERS += \
    boss.h \
    bullet.h \
    coins.h \
    door.h \
    enemy.h \
    enemy_2.h \
    health.h \
    heart.h \
    loggedinScreen.h \
    login.h \
    lostscreen.h \
    map.h \
    pausedscreen.h \
    player.h \
    signup.h \
    startingscreen.h \
    winningscreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    loggedinScreen.ui \
    login.ui \
    lostscreen.ui \
    pausedscreen.ui \
    signup.ui \
    startingscreen.ui \
    winningscreen.ui

RESOURCES += \
    resources.qrc
