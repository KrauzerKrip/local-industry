# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project("industry")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(lc_client)
add_library(stb INTERFACE)

add_subdirectory("res")
add_subdirectory("lc_client")
add_subdirectory("libs")

add_subdirectory("game")

set(CMAKE_CXX_SCAN_FOR_MODULES true)

target_include_directories(game PRIVATE lc_client)
target_link_libraries(game lc_client)