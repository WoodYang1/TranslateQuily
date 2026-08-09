QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += 3rdparty/QHotkey/qhotkey.h \
           3rdparty/QHotkey/qhotkey_p.h \
           dragwidget.h \
           global.h \
           hotkeymanager.h \
           settingdata.h \
           setwidget.h \
           translateinputwidget.h
SOURCES += 3rdparty/QHotkey/qhotkey.cpp \
           3rdparty/QHotkey/qhotkey_win.cpp \
           dragwidget.cpp \
           global.cpp \
           hotkeymanager.cpp \
           settingdata.cpp \
           setwidget.cpp \
           translateinputwidget.cpp
INCLUDEPATH += 3rdparty/QHotkey
SOURCES += \
    httpclient.cpp \
    main.cpp \
    traymanager.cpp \
    widget.cpp

HEADERS += \
    httpclient.h \
    traymanager.h \
    widget.h

FORMS += \
    setwidget.ui \
    translateinputwidget.ui \
    widget.ui
RC_FILE = Translate.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc
