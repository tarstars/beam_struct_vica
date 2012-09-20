#-------------------------------------------------
#
# Project created by QtCreator 2011-09-23T11:38:02
#
#-------------------------------------------------

QT       += core


TARGET = horrible_tenzor
CONFIG   += console
CONFIG   -= app_bundle

OBJECTS_DIR = tmp

TEMPLATE = app

INCLUDEPATH+=C:\\work\\GnuWin32\\include D:\\backup\\work\\fftw-3

LIBS+= -lfftw3-3 -LD:\\backup\\work\\fftw-3

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
    matrixFFTW.cpp \
    plan.cpp \
    storage.cpp \
    spacialmatrix.cpp \
    vector3c.cpp \
    planewave_c.cpp \
    matrix3_c.cpp

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
    matrixFFTW.h \
    plan.h \
    storage.h \
    spacialmatrix.h \
    vector3c.h \
    planewave_c.h \
    matrix3_c.h
