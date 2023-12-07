cmake_minimum_required (VERSION 3.13)

project(eng_debug)

target_sources(lc_client 
    PRIVATE
    "gui/debug_widget.h"
    "gui/debug_widget.cpp"
)