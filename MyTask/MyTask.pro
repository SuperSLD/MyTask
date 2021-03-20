QT       += core gui
QT += svg
QT += network
QT += sql
QT += websockets
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    common/base/basefragment.cpp \
    common/base/basescreensfactory.cpp \
    common/navigator.cpp \
    main.cpp \
    mainwindow.cpp \
    models/basemodel.cpp \
    models/cardmodel.cpp \
    models/checkboxmodel.cpp \
    models/deskmodel.cpp \
    models/historymodel.cpp \
    models/usermodel.cpp \
    screensfactory.cpp \
    style/stylecontainer.cpp \
    ui/auth/loginfragment.cpp \
    ui/auth/registrationfragment.cpp \
    ui/auth/startfragment.cpp \
    ui/desk/addcardfragment.cpp \
    ui/desk/adddeskfragment.cpp \
    ui/desk/createinvitefragment.cpp \
    ui/desk/deskfragment.cpp \
    ui/desk/historyfragment.cpp \
    ui/desk/userslistfragment.cpp \
    ui/invite/invitelistfragment.cpp \
    ui/mainfragment.cpp \
    ui/splashfragment.cpp \
    ui/view/boxid.cpp \
    ui/view/deskwidget.cpp \
    ui/view/invitewidget.cpp \
    ui/view/linewidget.cpp \
    ui/view/qsvgbutton.cpp \
    ui/view/userwidget.cpp \
    ui/view/waitingspinnerwidget.cpp

HEADERS += \
    common/base/basefragment.h \
    common/base/basescreensfactory.h \
    common/navigator.h \
    mainwindow.h \
    models/basemodel.h \
    models/cardmodel.h \
    models/checkboxmodel.h \
    models/deskmodel.h \
    models/historymodel.h \
    models/usermodel.h \
    screensfactory.h \
    style/stylecontainer.h \
    ui/auth/loginfragment.h \
    ui/auth/registrationfragment.h \
    ui/auth/startfragment.h \
    ui/desk/addcardfragment.h \
    ui/desk/adddeskfragment.h \
    ui/desk/createinvitefragment.h \
    ui/desk/deskfragment.h \
    ui/desk/historyfragment.h \
    ui/desk/userslistfragment.h \
    ui/invite/invitelistfragment.h \
    ui/mainfragment.h \
    ui/splashfragment.h \
    ui/view/boxid.h \
    ui/view/deskwidget.h \
    ui/view/invitewidget.h \
    ui/view/linewidget.h \
    ui/view/loadingwidget.h \
    ui/view/qsvgbutton.h \
    ui/view/userwidget.h \
    ui/view/waitingspinnerwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resc.qrc \
    resc.qrc


win32:RC_ICONS += resc/icon.ico
