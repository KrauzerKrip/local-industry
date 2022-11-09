cmake_minimum_required (VERSION 3.13)

project(util)

target_sources(lc_client 
    PRIVATE
        "resource.cpp"
        "resource.h"
        "directories.h"
        "directories.cpp"
        "file_util.h"
        "file_util.cpp"
        "image.h"
        "image.cpp"
        "i_resource.h"
)