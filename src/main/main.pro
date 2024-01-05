QT       += core gui
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20


SOURCES += \
    ../artikl.cpp \
    ../binaryserializer.cpp \
    ../glavnimeni.cpp \
    ../help.cpp \
    ../izvestaj.cpp \
    ../main.cpp \
    ../meni.cpp \
    ../naruci.cpp \
    ../porudzbina.cpp \
    ../raspored.cpp \
    ../rasporeddata.cpp \
    ../sto.cpp \
    ../tabla.cpp \
    ../unesiartikle.cpp \
    ../kategorija.cpp

HEADERS += \
    ../artikl.h \
    ../binaryserializer.h \
    ../glavnimeni.h \
    ../help.h \
    ../izvestaj.h \
    ../meni.h \
    ../naruci.h \
    ../porudzbina.h \
    ../raspored.h \
    ../rasporeddata.h \
    ../serializable.h \
    ../serializer.h \
    ../sto.h \
    ../tabla.h \
    ../unesiartikle.h \
    ../kategorija.h


FORMS += \
    ../glavnimeni.ui \
    ../help.ui \
    ../naruci.ui \
    ../unesiartikle.ui

