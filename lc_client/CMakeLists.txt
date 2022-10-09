cmake_minimum_required (VERSION 3.8)

project(lc_client)

add_library(lc_client SHARED "src/loop.cpp" 

							"include/lc_client/loop.h") 

#target_include_directories(lc_client}
    #PUBLIC
        #"$<INSTALL_INTERFACE:include>"
        #"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#)