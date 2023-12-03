QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/artikl.cpp \
    src/help.cpp \
    src/krenisaradom.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/porudzbina.cpp \
    src/stolovi.cpp \
    src/stozaprikaz.cpp \
    src/tabla.cpp \
    src/unesiartikle.cpp \
    src/urediporudzbinu.cpp

HEADERS += \
    src/artikl.h \
    src/help.h \
    src/krenisaradom.h \
    src/mainwindow.h \
    src/porudzbina.h \
    src/stolovi.h \
    src/stozaprikaz.h \
    src/tabla.h \
    src/unesiartikle.h \
    src/urediporudzbinu.h

FORMS += \
    mainwindow.ui \
    src/help.ui \
    src/krenisaradom.ui \
    src/stolovi.ui \
    src/unesiartikle.ui \
    src/urediporudzbinu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
