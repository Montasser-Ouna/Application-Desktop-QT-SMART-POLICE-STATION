QT += core gui
QT += sql
QT += widgets network
QT       += multimedia printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agent.cpp \
    connexion.cpp \
    enquette.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    suspect.cpp \
    temoignage.cpp

HEADERS += \
    agent.h \
    connexion.h \
    enquette.h \
    mainwindow.h \
    message.h \
    suspect.h \
    temoignage.h

FORMS += \
    connexion.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
