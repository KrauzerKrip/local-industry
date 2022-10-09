# CMakeList.txt : CMake project for industry, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project("industry")

file(GLOB SOURCES "lc_client/src/*.cpp" "lc_client/src/*/*.cpp" "lc_client/src/*/*/*.cpp" "lc_client/src/*/*/*/*.cpp")

add_library(lc_client ${SOURCES})
#add_library(lc_client::lc_client ALIAS lc_client)

target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:lc_client/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lc_client/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(industry game/main.cpp game/main.h)
target_link_libraries(industry lc_client)

# TODO: Add tests and install targets if needed.
