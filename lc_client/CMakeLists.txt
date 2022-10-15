cmake_minimum_required (VERSION 3.13)

project(lc_client)

target_sources(lc_client 
    PRIVATE
        "src/lc_client/eng_graphics/i_window.h"
        "src/lc_client/i_game_logic.h"

        "src/lc_client/loop.cpp"
        "src/lc_client/loop.h"
        "src/lc_client/eng_graphics/openGL/gl_window.cpp"
        "src/lc_client/eng_graphics/openGL/gl_window.h"

        "src/lc_client/exceptions/glfw_exceptions.h"
        "src/lc_client/exceptions/glad_exceptions.h"
        "src/lc_client/eng_input/glfw_input.h" "src/lc_client/eng_input/i_input.h" "src/lc_client/eng_input/glfw_input.cpp" "src/lc_client/exceptions/input_exceptions.h"
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
target_link_libraries(lc_client PUBLIC glfw glad::glad)

#target_compile_definitions(lc_client PUBLIC USE_BARRY) #for preprocessor definitions
target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:/include>
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
