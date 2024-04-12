cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE 
        "game_info.h"
        "game_info.cpp"
        "tier1.h"
        "tier1.cpp"
        "config.h"
        "config.cpp"
)