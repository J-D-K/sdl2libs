cmake_minimum_required(VERSION 3.30)

project("sdl2base")

set(SOURCE_FILES
    source/sdl2base.cpp
    source/window.cpp
    source/renderer.cpp
    source/input.cpp
    source/logger.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})