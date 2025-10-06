cmake_minimum_required (VERSION 3.10)
project(flappy-bird-sdl2)
include(FindPkgConfig)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_options(-Wall -Wempty-body -Werror -Warray-bounds -g)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/tests/*.cpp
        src/tests/*.h
        src/*.hpp
        src/*.h
)
set_source_files_properties(src/tests/test_hash.cpp
        PROPERTIES
        COMPILE_FLAGS "-Wno-error=unused-variable"
)
add_executable (${CMAKE_PROJECT_NAME} ${SOURCES})
target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/tests
)

message(STATUS "Building for native platform")
include(FetchContent)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.32.4
        FIND_PACKAGE_ARGS
)
FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.1
        FIND_PACKAGE_ARGS
)

FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.6
        FIND_PACKAGE_ARGS
)

FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.24.0
        FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(SDL2 SDL2_mixer SDL2_image SDL2_ttf)

target_include_directories (
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/src
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_mixer::SDL2_mixer
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
)