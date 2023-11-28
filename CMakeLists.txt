cmake_minimum_required(VERSION 3.7)

project (raycasting)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )


find_library(SDL2 NAMES "SDL2")
find_library(SDL2_image NAMES "SDL2_image")
find_library(SDL2_mixer NAMES "SDL2_mixer")



set(SOURCE_FILES main.cpp functions.cpp)


add_executable(raycasting ${SOURCE_FILES})
target_link_libraries(raycasting SDL2 SDL2_image SDL2_mixer)