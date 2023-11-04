cmake_minimum_required (VERSION 3.13)

project(eng_gui)

target_sources(lc_client 
    PRIVATE
    "gui_console.h"
    "gui_console.cpp"

    "text/text.h"
    "text/text.cpp"
)