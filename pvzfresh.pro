QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bucketzombie.cpp \
    button.cpp \
    car.cpp \
    card.cpp \
    cherrybomb.cpp \
    conezombie.cpp \
    footballzombie.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    normalzombie.cpp \
    other.cpp \
    pea.cpp \
    peashooter.cpp \
    plants.cpp \
    potatomine.cpp \
    repeater.cpp \
    screenzombie.cpp \
    shop.cpp \
    snowpeashooter.cpp \
    sun.cpp \
    sunflower.cpp \
    wallnut.cpp \
    zombie.cpp

HEADERS += \
    bucketzombie.h \
    button.h \
    car.h \
    card.h \
    cherrybomb.h \
    conezombie.h \
    footballzombie.h \
    mainwindow.h \
    map.h \
    normalzombie.h \
    other.h \
    pea.h \
    peashooter.h \
    plants.h \
    potatomine.h \
    repeater.h \
    screenzombie.h \
    shop.h \
    snowpeashooter.h \
    sun.h \
    sunflower.h \
    wallnut.h \
    zombie.h



CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
