cmake_minimum_required(VERSION 3.22.1)
project(raycasting)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_MakeAvailable(SDL2_image)

add_executable(raycasting main.cpp functions.cpp)
target_link_libraries(raycasting SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)