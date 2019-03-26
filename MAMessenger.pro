#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T13:50:18
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MAMessenger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp\
    mainwindow.cpp\
    authorization.cpp\
    creategroupe.cpp\
    findcontact.cpp\
    client.cpp\
    connectioncheck.cpp\
    jsonconverter.cpp \
    registration.cpp \
    generalpage.cpp \
    contacts.cpp \
    groups.cpp \
    channals.cpp \
    joingroup.cpp \
    joinchannal.cpp \
    createchannal.cpp \
    fileworking.cpp \
    getfromserver.cpp\
    getfromfile.cpp \
    messageing.cpp \
    addcontact.cpp


HEADERS += \
    mainwindow.h\
    authorization.h\
    creategroupe.h\
    findcontact.h\
    client.h\
    connectioncheck.h\
    jsonconverter.h \
    registration.h \
    generalpage.h \
    contacts.h \
    groups.h \
    channals.h \
    joingroup.h \
    joinchannal.h \
    createchannal.h \
    fileworking.h \
    getfromserver.h\
    getfromfile.h \
    messageing.h \
    addcontact.h

FORMS += \
    mainwindow.ui\
    authorization.ui\
    creategroupe.ui\
    findcontact.ui \
    registration.ui \
    generalpage.ui \
    contacts.ui \
    groups.ui \
    channals.ui \
    joingroup.ui \
    joinchannal.ui \
    createchannal.ui \
    messageing.ui \
    addcontact.ui
