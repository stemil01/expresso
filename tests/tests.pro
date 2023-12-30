TEMPLATE = app
QT += widgets

CONFIG += c++20

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

SOURCES += \
    artikl_test.cpp \
    main.cpp \
    naruci_test.cpp \
    porudzbina_test.cpp \
    raspored_test.cpp \
    sto_glmeni_test.cpp \
    sto_test.cpp \
    ../src/artikl.cpp \
    ../src/binaryserializer.cpp \
    ../src/glavnimeni.cpp \
    ../src/help.cpp \
    ../src/izvestaj.cpp \
    ../src/naruci.cpp \
    ../src/porudzbina.cpp \
    ../src/raspored.cpp \
    ../src/rasporeddata.cpp \
    ../src/sto.cpp \
    ../src/tabla.cpp \
    ../src/unesiartikle.cpp \
    ../src/meni.cpp
    #unesiartikle_test.cpp

HEADERS += \
    ../src/artikl.h \
    ../src/binaryserializer.h \
    ../src/glavnimeni.h \
    ../src/help.h \
    ../src/izvestaj.h \
    ../src/naruci.h \
    ../src/porudzbina.h \
    ../src/raspored.h \
    ../src/rasporeddata.h \
    ../src/serializable.h \
    ../src/serializer.h \
    ../src/sto.h \
    ../src/tabla.h \
    ../src/unesiartikle.h \
    ../src/meni.h

FORMS += \
    ../src/glavnimeni.ui \
    ../src/help.ui \
    ../src/naruci.ui \
    ../src/unesiartikle.ui
