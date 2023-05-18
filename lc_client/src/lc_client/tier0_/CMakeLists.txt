cmake_minimum_required (VERSION 3.13)

project(tier0)

target_sources(lc_client 
    PRIVATE
        "console/i_console.h"
        "console/console.h"
        "console/console.cpp"
        "console/events.h"
        "console/events.cpp"
)