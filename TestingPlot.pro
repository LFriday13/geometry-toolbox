QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CircleNode.cpp \
    Dialogs/AddLineDialogs/addlinefirsttangent.cpp \
    Dialogs/AddLineDialogs/addlineparallel.cpp \
    Dialogs/AddLineDialogs/addlineperpendicularbisector.cpp \
    Dialogs/AddLineDialogs/addlinesecondtangent.cpp \
    Dialogs/AddLineDialogs/addlinethrough.cpp \
    Dialogs/AddPointDialogs/addpointindependent.cpp \
    Dialogs/AddPointDialogs/addpointintersect.cpp \
    Dialogs/AddPointDialogs/addpointmidpoint.cpp \
    Dialogs/AddPointDialogs/addpointon.cpp \
    Dialogs/AddPointDialogs/addpointoncircle.cpp \
    Dialogs/AddPointDialogs/addpointsecondintersect.cpp \
    Dialogs/AddTriangleCenterDialogs/addtrianglecenter.cpp \
    Dialogs/AddTriangleDialogs/addtriangle.cpp \
    GeoComponents.cpp \
    GeoNode.cpp \
    LineNode.cpp \
    PointNode.cpp \
    TriangleCentersNode.cpp \
    TriangleNode.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    CircleNode.h \
    Dialogs/AddLineDialogs/addlinefirsttangent.h \
    Dialogs/AddLineDialogs/addlineparallel.h \
    Dialogs/AddLineDialogs/addlineperpendicularbisector.h \
    Dialogs/AddLineDialogs/addlinesecondtangent.h \
    Dialogs/AddLineDialogs/addlinethrough.h \
    Dialogs/AddPointDialogs/addpointindependent.h \
    Dialogs/AddPointDialogs/addpointintersect.h \
    Dialogs/AddPointDialogs/addpointmidpoint.h \
    Dialogs/AddPointDialogs/addpointon.h \
    Dialogs/AddPointDialogs/addpointoncircle.h \
    Dialogs/AddPointDialogs/addpointsecondintersect.h \
    Dialogs/AddTriangleCenterDialogs/addtrianglecenter.h \
    Dialogs/AddTriangleDialogs/addtriangle.h \
    GeoComponents.h \
    GeoNode.h \
    LineNode.h \
    PointNode.h \
    TriangleCentersNode.h \
    TriangleNode.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    Dialogs/AddLineDialogs/addlinefirsttangent.ui \
    Dialogs/AddLineDialogs/addlineparallel.ui \
    Dialogs/AddLineDialogs/addlineperpendicularbisector.ui \
    Dialogs/AddLineDialogs/addlinesecondtangent.ui \
    Dialogs/AddLineDialogs/addlinethrough.ui \
    Dialogs/AddPointDialogs/addpointindependent.ui \
    Dialogs/AddPointDialogs/addpointintersect.ui \
    Dialogs/AddPointDialogs/addpointmidpoint.ui \
    Dialogs/AddPointDialogs/addpointon.ui \
    Dialogs/AddPointDialogs/addpointoncircle.ui \
    Dialogs/AddPointDialogs/addpointsecondintersect.ui \
    Dialogs/AddTriangleCenterDialogs/addtrianglecenter.ui \
    Dialogs/AddTriangleDialogs/addtriangle.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
