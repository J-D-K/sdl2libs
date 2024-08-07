cmake_minimum_required(VERSION 3.30)

project("sdllib")

set(SOURCE_FILES
    source/sdllib.cpp
    source/logger.cpp
    source/graphics/window.cpp
    source/graphics/renderer.cpp
    source/graphics/font.cpp
    source/input/input.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})