QT       += core gui
#Pour pouvoir utiliser QTcpSocket :
QT += network
QT += webenginewidgets
QT += gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += C:\Users\al457744\Desktop\Projet_3A_Wifiboot-main\opencv\build\include
# Linker flags for OpenCV library
LIBS += "C:\Users\al457744\Desktop\Projet_3A_Wifiboot-main\opencv\build\x64\vc16\lib\*.lib"
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myrobot.cpp

HEADERS += \
    mainwindow.h \
    myrobot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
