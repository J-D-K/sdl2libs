# Almost everything is set in this main parent list
cmake_minimum_required(VERSION 3.30)

project(sdl2libs)

set(CXX_STANDARD_REQUIRED 23)

add_compile_options(-Wall -O2)

include(FindFreetype)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Freetype REQUIRED)

set(INCLUDE_DIRS
    sdllib/include
    sdllib/include/graphics
    sdllib/include/input)

include_directories(${INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})

add_subdirectory(sdllib)
add_subdirectory(TestingApp)