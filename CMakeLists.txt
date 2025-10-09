cmake_minimum_required (VERSION 3.10)
project(flappy-bird-sdl2)
include(FindPkgConfig)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_options(-Wall -Wempty-body -Werror -Warray-bounds -g)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/system/*.cpp
        src/system/*.h
        src/draw/*.h
        src/draw/*.cpp
        src/game/*.h
        src/game/*.cpp
        src/utils/*.h
        src/utils/*.cpp
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
        ${PROJECT_SOURCE_DIR}/src/system
        ${PROJECT_SOURCE_DIR}/src/draw
        ${PROJECT_SOURCE_DIR}/src/game
        ${PROJECT_SOURCE_DIR}/src/utils
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

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.13.2
)

set(BOOST_INCLUDE_LIBRARIES json)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(SDL2 SDL2_mixer SDL2_image SDL2_ttf Boost entt)

target_include_directories (
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/system
        ${PROJECT_SOURCE_DIR}/src/draw
        ${PROJECT_SOURCE_DIR}/src/game
        ${PROJECT_SOURCE_DIR}/src/utils
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
        EnTT::EnTT
        Boost::json
)

file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR} )
file(COPY ${PROJECT_SOURCE_DIR}/gfx DESTINATION ${CMAKE_BINARY_DIR} )
file(COPY ${PROJECT_SOURCE_DIR}/audio DESTINATION ${CMAKE_BINARY_DIR} )

target_compile_definitions(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ATLAS_FILE_PATH="${CMAKE_BINARY_DIR}/data/atlas.json"
        DATA_DIR="${CMAKE_BINARY_DIR}/data"
        GFX_DIR="${CMAKE_BINARY_DIR}/gfx"
        AUDIO_DIR="${CMAKE_BINARY_DIR}/audio"
)