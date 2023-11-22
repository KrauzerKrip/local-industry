# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project("industry")

add_library(lc_client)
add_library(stb INTERFACE)

add_subdirectory("res")
add_subdirectory("lc_client")
add_subdirectory("libs")
add_subdirectory("game")

add_executable(industry "game/main.cpp" "game/main.h" "game/game.cpp" "game/game.h")

target_include_directories(industry PRIVATE lc_client)
target_link_libraries(industry lc_client)