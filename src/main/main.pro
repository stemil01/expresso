QT       += core gui
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../artikl.cpp \
    ../binaryserializer.cpp \
    ../glavnimeni.cpp \
    ../help.cpp \
    ../izvestaj.cpp \
    ../main.cpp \
    ../naruci.cpp \
    ../porudzbina.cpp \
    ../raspored.cpp \
    ../rasporeddata.cpp \
    ../sto.cpp \
    ../tabla.cpp \
    ../unesiartikle.cpp

HEADERS += \
    ../artikl.h \
    ../binaryserializer.h \
    ../glavnimeni.h \
    ../help.h \
    ../izvestaj.h \
    ../naruci.h \
    ../porudzbina.h \
    ../raspored.h \
    ../rasporeddata.h \
    ../serializable.h \
    ../serializer.h \
    ../sto.h \
    ../tabla.h \
    ../unesiartikle.h


FORMS += \
    ../glavnimeni.ui \
    ../help.ui \
    ../naruci.ui \
    ../unesiartikle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
