cmake_minimum_required(VERSION 3.13)

project(game)

add_executable(game "src/game/main.cpp" "src/game/main.h" "src/game/game.cpp" "src/game/game.h")

add_subdirectory("src/game/gui")
#add_subdirectory("src/game/gui")

target_include_directories(game
    PUBLIC
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
