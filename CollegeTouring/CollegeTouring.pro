QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcampuses.cpp \
    databaseviewform.cpp \
    dbmanager.cpp \
    initialfromuciform.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modifysouvenirs.cpp \
    shoppingcart.cpp

HEADERS += \
    addcampuses.h \
    databaseviewform.h \
    dbmanager.h \
    initialfromuciform.h \
    logindialog.h \
    mainwindow.h \
    modifysouvenirs.h \
    shoppingcart.h

FORMS += \
    addcampuses.ui \
    databaseviewform.ui \
    initialfromuciform.ui \
    logindialog.ui \
    mainwindow.ui \
    modifysouvenirs.ui \
    shoppingcart.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
