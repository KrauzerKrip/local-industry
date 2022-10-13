# CMakeList.txt : CMake project for industry, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

project("industry")

#file(GLOB SOURCES "lc_client/src/*.cpp" "lc_client/src/*/*.cpp" "lc_client/src/*/*/*.cpp" "lc_client/src/*/*/*/*.cpp")
#file(GLOB HEADERS "lc_client/include/lc_client/*.h" "lc_client/include/lc_client/*/*.h" "lc_client/include/lc_client/*/*/*.h" "lc_client/include/lc_client/*/*/*/*.h")

add_library(lc_client)
#add_library(lc_client::lc_client ALIAS lc_client)

target_sources(lc_client PRIVATE
   "lc_client/src/eng_graphics/openGL/gl_window.cpp"
   "lc_client/include/lc_client/eng_graphics/i_window.h"
   "lc_client/src/exceptions/glfw_exceptions.h"
   "lc_client/src/exceptions/glad_exceptions.h"

   "lc_client/include/lc_client/eng_graphics/i_window.h"
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
target_link_libraries(lc_client PUBLIC glfw glad::glad)

target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:lc_client/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lc_client/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lc_client/src>
)

add_executable(industry "game/main.cpp" "game/main.h" "game/game.cpp" "game/game.h" )
target_link_libraries(industry lc_client)

# TODO: Add tests and install targets if needed.
 