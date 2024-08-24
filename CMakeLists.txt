cmake_minimum_required(VERSION 3.28)
project(Kafic VERSION 1.00)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(CMAKE_PREFIX_PATH "/home/jelena/Qt/6.6.3")
set(Qt6_DIR "/home/jelena/Qt/6.6.3/gcc_64/lib/cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ATOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

 
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


include_directories("/home/jelena/Qt/6.6.3/gcc_64/include")




set(SOURCE
	src/artikl.cpp
	src/binaryserializer.cpp
	src/glavnimeni.cpp
	src/help.cpp
	src/izvestaj.cpp
	src/kategorija.cpp
	src/main.cpp
	src/meni.cpp
	src/naruci.cpp
	src/porudzbina.cpp
	src/raspored.cpp
	src/rasporeddata.cpp
	src/sto.cpp
	src/tabla.cpp
	src/unesiartikle.cpp
)

set(HEADERS
	src/artikl.h
	src/binaryserializer.h
	src/glavnimeni.h
	src/help.h
	src/izvestaj.h
	src/kategorija.h
	src/meni.h
	src/naruci.h
	src/porudzbina.h
	src/raspored.h
	src/rasporeddata.h
	src/serializable.h
	src/serializer.h
	src/sto.h
	src/tabla.h
	src/tableoptions.h
	src/unesiartikle.h
)

set(FORMS
	src/glavnimeni.ui
	src/help.ui
	src/naruci.ui
	src/tableoptions.ui
	src/unesiartikle.ui
)

qt6_wrap_ui(UI_HEADERS ${FORMS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)

install(TARGETS ${PROJECT_NAME} DESTINATION /opt/${PROJECT_NAME}/bin)



