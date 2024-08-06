# Almost everything is set in this main parent list
cmake_minimum_required(VERSION 3.30)

project(sdl2libs)

set(CXX_STANDARD_REQUIRED 23)

add_compile_options(-Wall -O2)

include(FindFreetype)

find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

include_directories(sdl2font/include sdl2base/include ${FREETYPE_INCLUDE_DIRS})

add_subdirectory(sdl2base)
add_subdirectory(sdl2font)
add_subdirectory(TestingApp)