QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    campusselectdialog.cpp \
    addcampuses.cpp \
    databaseviewform.cpp \
    dbmanager.cpp \
    displaypurchases.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modifysouvenirs.cpp \
    numberinputdialog.cpp \
    purchasewindow.cpp \
    shoppingcart.cpp \
    tripRoutePlanner.cpp

HEADERS += \
    campusselectdialog.h \
    addcampuses.h \
    databaseviewform.h \
    dbmanager.h \
    displaypurchases.h \
    logindialog.h \
    mainwindow.h \
    modifysouvenirs.h \
    numberinputdialog.h \
    purchasewindow.h \
    shoppingcart.h \
    tripRoutePlanner.h

FORMS += \
    campusselectdialog.ui \
    addcampuses.ui \
    databaseviewform.ui \
    displaypurchases.ui \
    logindialog.ui \
    mainwindow.ui \
    modifysouvenirs.ui \
    numberinputdialog.ui \
    purchasewindow.ui \
    shoppingcart.ui \
    tripRoutePlanner.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
