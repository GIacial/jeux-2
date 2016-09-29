#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T14:47:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecondJeux
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    entite.cpp \
    interfacecombat.cpp \
    ennemie.cpp \
    hero.cpp \
    fenetremagie.cpp \
    attaque.cpp \
    buff.cpp \
    menuprincipal.cpp \
    systemcombat.cpp \
    afficheurpvmagie.cpp \
    qwidgetcliquable.cpp

HEADERS  += mainwindow.h \
    entite.h \
    interfacecombat.h \
    ennemie.h \
    hero.h \
    fenetremagie.h \
    attaque.h \
    buff.h \
    menuprincipal.h \
    systemcombat.h \
    afficheurpvmagie.h \
    qwidgetcliquable.h

OTHER_FILES += \
    Memo.txt
