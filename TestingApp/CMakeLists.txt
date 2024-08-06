cmake_minimum_required(VERSION 3.30)

project("sdl2libsApp")

set(SOURCE_FILES
    source/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_directories(${PROJECT_NAME} PUBLIC ./sdl2base PUBLIC ./sdl2font)
target_link_libraries(${PROJECT_NAME} sdl2base sdl2font SDL2 freetype)

