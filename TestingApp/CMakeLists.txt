cmake_minimum_required(VERSION 3.30)

project("testapp")

include_directories("include")

set(SOURCE_FILES
    source/main.cpp
    source/game.cpp
    source/titlestate.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_directories(${PROJECT_NAME} PUBLIC ./sdl2base PUBLIC ./sdl2font)
target_link_libraries(${PROJECT_NAME} sdllib SDL2 SDL2_image freetype)

