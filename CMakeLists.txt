cmake_minimum_required(VERSION 3.14)
project(trainLab)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/sfml/SFML/include")
set(SFML_LIBRARY_DIR "/sfml/SFML/lib")
set(SFML_DIR "/sfml/SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(trainLab main.cpp Train.cpp Train.h Station.cpp Station.h Map.cpp Map.h railWay.h)
target_link_libraries (trainLab  sfml-graphics sfml-window sfml-system)