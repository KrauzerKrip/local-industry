cmake_minimum_required (VERSION 3.13)

project(util)

target_sources(lc_client 
    PRIVATE
        "resource_loader.cpp"
        "resource_loader.h"
)