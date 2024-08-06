cmake_minimum_required(VERSION 3.30)

project("sdl2font")

set(SOURCE_FILES
    source/sdl2font.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})