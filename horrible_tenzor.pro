#-------------------------------------------------
#
# Project created by QtCreator 2011-09-23T11:38:02
#
#-------------------------------------------------

QT       += core


TARGET = horrible_tenzor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH+=C:\work\GnuWin32\include\

LIBS+= -lfftw3

SOURCES += main.cpp \
    util.cpp \
    tensor.cpp \
    vector3.cpp \
    matrix3.cpp \
    polinom.cpp \
    matrix.cpp \
    polymatrix.cpp \
    wavematrix.cpp \
    waveelement.cpp \
    wavecomposit.cpp \
    planewave.cpp \
    tests.cpp \
    matrixfftw.cpp \
    plan.cpp \
    storage.cpp

HEADERS += \
    tensor.h \
    util.h \
    vector3.h \
    matrix3.h \
    polinom.h \
    types.h \
    matrix.h \
    polymatrix.h \
    wavematrix.h \
    waveelement.h \
    wavecomposit.h \
    planewave.h \
    matrixfftw.h \
    plan.h \
    storage.h
