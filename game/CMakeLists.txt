cmake_minimum_required(VERSION 3.8)

project(game)

add_executable(game "main.cpp" "main.h")

target_include_directories(game PRIVATE lc_client)
target_link_libraries(game lc_client)