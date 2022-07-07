cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(name "COPYTEXT")
project(${name})

message("CMAKE_SYSTEM_NAME " ${CMAKE_SYSTEM_NAME})

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

set(SOURCES dialog.cpp main.cpp mainwindow.cpp) 
set(HEADERS dialog.h mainwindow.h)
set(UI dialog.ui mainwindow.ui)

add_executable(${name} ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(${name} Qt5::Widgets)

set_target_properties(${name} PROPERTIES WIN32_EXECUTABLE TRUE)
