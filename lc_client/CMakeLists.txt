cmake_minimum_required (VERSION 3.13)

project(lc_client)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
target_link_libraries(lc_client PUBLIC glfw glad::glad EnTT::EnTT)

target_link_libraries(lc_client PRIVATE eng::rc)
target_link_libraries(lc_client PRIVATE stb)

target_sources(lc_client 
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/i_game_logic.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.h"
)

add_subdirectory("include/ldk_client/local_engine")

add_subdirectory("src/lc_client/local_engine")

add_subdirectory("src/lc_client/eng_graphics")
add_subdirectory("src/lc_client/eng_entties")
add_subdirectory("src/lc_client/eng_input")
add_subdirectory("src/lc_client/eng_procedures")
add_subdirectory("src/lc_client/eng_scene")
add_subdirectory("src/lc_client/exceptions")
add_subdirectory("src/lc_client/util")

#target_compile_definitions(lc_client PUBLIC USE_BARRY) #for preprocessor definitions
target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:/include>
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
